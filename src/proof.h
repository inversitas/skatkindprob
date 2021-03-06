#ifndef PROOF_H
#define PROOF_H
#include <gmpxx.h>

#include <atomic>
#include <future>
#include <iostream>
#include <random>
#include <string>
#include <thread>

#include "hand_tree.h"
#include "io.h"

// This class calculates the probabilites for n three of a kind in a game of
// skat using the following method:
// 1. generate all possible games using 3 hands to represent a game
//    (for further information on hands take a look at hand_tree.h)
// 2. count how many of the 3 hand combinations have 0 - 8 three of a kind
// 3. adjust the weight of each 3 hand combination (each 3 hand combination
//    represents a number of real games)
// 4. sum everything up

class Proof {
 public:
  Proof();
  ~Proof();
  void compute(unsigned int numberOfThreads);

 private:
  // returns "multiplicity" of hand combination
  // (how many real games are represented by a combiantion of hands)
  unsigned long calcMultiplicity(const Hand &p1h, const Hand &p2h,
                                 const Hand &p3h);

  // returns number of three of a kind in hands p1,p2,p3
  unsigned long calcN3Kind(const Hand &p1h, const Hand &p2h, const Hand &p3h);

  // to improve performance the computation is multithreaded
  std::array<mpz_class, 10> computeThread(std::vector<Hand> p1HandsPart);

  // binominal coefficient look up table
  std::array<std::vector<unsigned long>, 5> bncLookup;

  // atomic unsigned int keeping track of the progress
  std::atomic<unsigned int> progress;
};

#endif  // PROOF_H
