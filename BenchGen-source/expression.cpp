/*
Maintained by Walter Brown
Open for modification to others in Maciej Ciesielski's team.
*/
#define DEBUG_EXPRESSION 0
#define TO_STRING_RESERVE 0 /* reservation proved to be inefficient here. */
#define TERM_TO_STRING_RESERVE 0
                            /* No noticable time improvement, mem increased. */

#include "expression.h"

#if DEBUG_EXPRESSION
  #include <iostream>
#endif

Expression::Expression()
{
}

Expression::Expression(const string& s)
{
  string mutableString = s;
  add(mutableString);
}

void Expression::add(const Expression& e)
{
  /* Add in every element of the map. */
  for(auto kv : e.terms)
  {
    addToCoefficients(kv.first, kv.second.coefficient);
  }
}

void Expression::add(string& exp)
{
  #if DEBUG_EXPRESSION
    cout << "Expression::add, exp=\"" << exp << "\"" << endl;
  #endif
  /* Count "" as 0. */
  if(exp.length() == 0) return;

  /* Put the string in sum of products form. */
  StringMath::toUseful(exp);
  StringMath::simplify(exp);

  #if DEBUG_EXPRESSION
    cout << "After stringmath, exp=\"" << exp << "\"" << endl;
  #endif

  /* Split to terms. */
  vector<string> terms;
  StringMath::split(exp, '+', terms);

  /* Put terms in coefficient map. */
  for(string& t : terms)
  {
    int coefBorder = t.find('*');
    /* If this has no variables, goes in "1" */
    string index;
    if(coefBorder == string::npos)
    {
      index = "1";
      addToCoefficients(index, t);
    }
    else
    {
      index = t.substr(coefBorder+1);
      string number = t.substr(0, coefBorder);
      addToCoefficients(index, number);
    }
  }
  #if DEBUG_EXPRESSION
    cout << "done with Expression::add" << endl;
  #endif
}

void Expression::add(const Term& t)
{
  /* Don't bother if this is just a zero. */
  if(t.coefficient == 0) return;
  string index;
  /* If this is a constant, you don't need to deal with variable stringing. */
  if(t.variables.size() == 0)
  {
    index = "1";
  }
  else
  {
    /* Let toString parse them. */
    index = t.toString();
    /* Pull off the coefficient. */
    index = index.substr(index.find('*')+1);
  }
  addToCoefficients(index, t.coefficient);
}

void Expression::addToCoefficients(const string& index, const string& value)
{
  /* Convert the string to something you can add. */
  mpz_class val;
  val = value.c_str();

  addToCoefficients(index, val);
}

void Expression::addToCoefficients(const string& index, const mpz_class& value)
{
  /* See if this element is in the coefficients map. */
  auto indexPointer = terms.find(index);
  if(indexPointer == terms.end())
  {
    /* If not, just add this to the map. */
    Term* t = &terms[index];
    t->coefficient = value;
    /* As a new element, you should also give it a variable list. */
    if(index != "1")
    {
      vector<string> v;
      StringMath::split(index, '*', v);
      for(string i : v)
      {
        t->variables.insert(i);
      }
    }
  }
  else
  {
    /* If so, do addition. */
    indexPointer->second.coefficient += value;
    /* Terms with a coefficient of 0 are dropped. */
    if(indexPointer->second.coefficient == 0)
    {
      terms.erase(indexPointer);
    }
  }
}

void Expression::clear(void)
{
  terms.clear();
}

mpz_class Expression::coefficientOf(const string& monomial) const
{
  #if DEBUG_EXPRESSION
    cout << "Entering Expression::coefficientOf(" << monomial << ")" << endl;
  #endif
  Term t;
  likeTerm(monomial, t);
  return t.coefficient;

  #if DEBUG_EXPRESSION
    cout << "Exiting Expression::coefficientOf" << endl;
  #endif
}

void Expression::likeTerm(const string& similarTo, Term& result) const
{
  /* Break string into variables. */
  vector<string> multipliers;
  StringMath::split(similarTo, '*', multipliers);
  /* We want to focus on the variables. */
  vector<string> vars;
  vars.reserve(multipliers.size());
  for(string i : multipliers)
  {
    if(!StringMath::isNumber(i))
    {
      vars.push_back(i);
    }
  }
  /* If there's nothing here at this point, the constant term is wanted. */
  if(vars.size() == 0)
  {
    auto termPointer = terms.find("1");
    /* If there's no such term, you must build one. */
    if(termPointer == terms.end())
    {
      result.coefficient = 0;
    }
    else
    {
      result = termPointer->second;
    }
  }
  /* Otherwise, you need to do more work to look up the term. */
  else
  {
    /* Place in proper order. */
    StringMath::alphabeticalSort(vars.begin(), vars.end());
    /* Rejoin. */
    string monomial;
    StringMath::join(vars, '*', monomial);
    /* Now it's in the proper format to be checked in the term map. */
    auto termPointer = terms.find(monomial);
    if(termPointer == terms.end())
    {
      result.coefficient = 0;
    }
    else
    {
      result = terms.at(monomial);
    }
  }
}

unsigned int Expression::numberOfTerms(void) const
{
  return terms.size();
}

void Expression::substitute(string var, const Expression& replacement)
{
  /* Remove spaces. */
  StringMath::removeAll(var, ' ');
  /* This will store the transformed terms. */
  Expression bonus;
  /* Extract the right bonus from each term. */
  for(auto it = terms.begin(); it != terms.end();)
  {
    /* If this term contains x, it will be replaced by a bonus. */
    auto varPointer = it->second.variables.find(var);
    if(varPointer != it->second.variables.end())
    {
      /* We'll reuse the "it" term as a base for its bonuses. */
      /* No bonus will have a "var".  Remove it now */
      it->second.variables.erase(varPointer);
      /* A bonus term will be added for each term of the replacement. */
      for(auto t : replacement.terms)
      {
        /* Make a copy of original term to work with. */
        Term bonusTerm = it->second;
        /* Multiply this bonus term with the term of the replacement. */
        bonusTerm.multiplyBy(t.second);
        /* Now this is ready to be in the bonus. */
        bonus.add(bonusTerm);
      }
      /* This term is being replaced.  It must go. */
      terms.erase(it++);
    }
    /* Otherwise, move on. */
    else
    {
      ++it;
    }
  }
  /* Finally, add the bonus. */
  add(bonus);
}

void Expression::substitute(const string& variable, const string& replacement)
{
  Expression rep(replacement);
  substitute(variable, rep);
}

Expression::operator string()
{
  return toString();
}

string Expression::toString (void) const
{
  #if DEBUG_EXPRESSION
    cout << "Entering Expression::toString" << endl;
  #endif
  
  /* If there's nothing in the map, return 0. */
  if(terms.empty()) return "0";
  #if DEBUG_EXPRESSION
    cout << "Moved passed empty 0 check." << endl;
  #endif

  string result;
  #if TO_STRING_RESERVE == 1
    /*
    Each entry will have a * between coef and vars and a + in back. Also,
    it's possible that the coefficient might need room for a sign.
    */
    size_t reserve = 3*terms.size();
    for(auto kv : terms)
    {
      /* Need room for coefficient. */
      reserve +=  mpz_sizeinbase(kv.second.coefficient.get_mpz_t(), 10);
      /* Need room for variables. */
      reserve += kv.first.size();
    }
    result.reserve(reserve);
  #endif
  #if TO_STRING_RESERVE == 2 /* Precalculate toStrings and put them in list. */
    /* Reserve space for + signs. */
    size_t reserve = terms.size();
    list<string> toStrings;
    for(auto kv : terms)
    {
      toStrings.push_back(kv.second.toString());
    }
    for(string s : toStrings)
    {
      reserve += toStrings.size();
    }
    result.reserve(reserve);
    for(string s : toStrings)
    {
      result += s + '+';
    }
  #endif
  #if TO_STRING_RESERVE != 2 /* Method 2 handles result construction. */
    /* Concatanate map back into a string. */
    for(auto kv : terms)
    {
      result += kv.second.toString() + '+';
    }
  #endif
  /* Oops!  We have an extra '+' at the end! */
  result.pop_back();
  #if DEBUG_EXPRESSION
    cout << "Finished pop_back.  result="<< result << endl;
  #endif

  /* Use stringmath to clean up the result. */
  StringMath::orderTerms(result);
  #if DEBUG_EXPRESSION
    cout << "Finished ordereTerms.  result="<< result << endl;
  #endif
  StringMath::toHuman(result);
  #if DEBUG_EXPRESSION
    cout << "Finished toHuman.  result="<< result << endl;
  #endif

  /* Return. */
  #if DEBUG_EXPRESSION
    cout << "About to exit Expression::toString" << endl;
  #endif
  return result;
}

void Expression::toVector(vector<Expression::Term>& result) const
{
  /* Reserve enough space to store the new items. */
  result.reserve(result.size() + numberOfTerms());
  /* Load. */
  for(auto kv : terms)
  {
    result.push_back(kv.second);
  }
}

void Expression::Term::multiplyBy(const Expression::Term& mult)
{
  /* Multiply coefficient. */
  coefficient *= mult.coefficient;
  /* Add the multiplier's variables to your set. */
  for(string i : mult.variables)
  {
    variables.insert(i);
  }
}

string Expression::Term::toString(void) const
{
  /* Start with the coefficient. */
  string result = coefficient.get_str();
  #if TERM_TO_STRING_RESERVE
  /* Reserve your space. */
    int reserveNeeded = result.size();
    for(auto i : variables)
    {
      reserveNeeded += i.size() + 1;
    }
    result.reserve(reserveNeeded);
  #endif
  /* Append all variables. */
  for(auto i : variables)
  {
    result += '*' + i;
  }
  return result;
}

Expression::Term::operator string()
{
  return toString();
}

ostream& operator << (ostream& strm, const Expression& expr)
{
  return strm << expr.toString();
}

ostream& operator << (ostream& strm, const Expression::Term& term)
{
  return strm << term.toString();
}

bool operator == (const Expression& a, const Expression& b)
{
  /* These can't be the same if they have a different number of terms. */
  if(a.numberOfTerms() != b.numberOfTerms()) return false;

  /* Compare term by term. */
  for(auto kv : a.terms)
  {
    /* If a has an element that's not in b, these don't match. */
    if(b.terms.find(kv.first) == b.terms.end()) return false;

    /* If b's version of the term has a different coefficient, no match. */
    if(b.terms.at(kv.first).coefficient != kv.second.coefficient) return false;
  }

  /* If no differences were found, these match. */
  return true;
}

bool operator != (const Expression& a, const Expression& b)
{
  return !(a == b);
}
