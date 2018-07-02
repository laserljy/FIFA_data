// ScoreTime.h
// Predicate comparison fo

#ifndef SCORE_TIME_H_
#define SCORE_TIME_H_

// note： in sort(vec.begin(), vec.end(), comp), it is the *iterator that will be passed into the comp, instead of iter, 
// in another word, it is the elem that is passed to the comp, not the pointer to the elem

class ScoreTime{
  public:
  	bool operator()( Goal& g1,  Goal& g2){ 
  		return g1.getGoalTime() < g2.getGoalTime();    
  		// return (g1.getGoalTime() - g2.getGoalTime());
  		
  		// !!! Two hours of debugging!!! to find that Functor must return bool!!! NOT integer!!!
  		// Lesson learned: Be specific and explict about the types!!!! NOT the implicit conversion, which could be tricky in C++
  		// TODO: a review on 3 ways for defining comparators:
  		// 1. overload operator <, and there are 2 implementation: a) within the class; b) outside the class, 2 params, and this could a friend function inside the class
  		// 2. define a function: bool myComp(const myObj& obj1, const myObj& obj2){...}
  		// 3. define a function object, functor, like what is done here, but functor can be used for many other case.
  		// note: C++11 <function> - C++11 brought new changes to how functors were handled. In addition, anonymous functions (lambdas) are now supported.


  	}
};

#endif // SCORE_TIME_H_
