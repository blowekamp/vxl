// This is vxl/vnl/vnl_unary_function.h
#ifndef vnl_unary_function_h_
#define vnl_unary_function_h_
#ifdef __GNUC__
#pragma interface
#endif

//:
//  \file
//  \brief Abstract 1D map
//
//  vnl_unary_function is an abstract map between two types (read spaces).
//
//  \author Andrew W. Fitzgibbon, Oxford RRG
//  \date   28 Nov 98
// \verbatim
// Modifications
//  981128 AWF Initial version.
//  LSB Manchester 19/3/01 Documentation tidied
//   Feb.2002 - Peter Vanroose - brief doxygen comment placed on single line
// \endverbatim
//
//-----------------------------------------------------------------------------

#include <vnl/vnl_numeric_limits.h>

//: Abstract 1D map between two types (read spaces)
template <class Return, class Argument>
class vnl_unary_function {
public:
  typedef vnl_numeric_limits<Return> limits;

  //: Apply the function.
  // The name is "f" rather than operator(), as the function will generally be
  // called through a pointer.  Note that the function is NOT const when you subclass.
  virtual Return f(Argument const& i) = 0;
#if 0
  //: Return bounding cube of domain (inputs).
  // Removed by awf simply to avoid implementing vnl_numeric_limits<vnl_vector<T> >.
  virtual Argument get_domain_min() const { return vnl_numeric_limits<Argument>::min(); }
  virtual Argument get_domain_max() const { return vnl_numeric_limits<Argument>::max(); }
#endif
  //: Return bounding cube of range (outputs)
  virtual Return get_range_min() const { return vnl_numeric_limits<Return >::min(); }
  virtual Return get_range_max() const { return limits::max(); }

  //: Copy should allocate a copy of this on the heap and return it.
  // If Subclasses do not implement this function, it will return null, but many
  // applications will never call it, so this may not be a problem for you.
  virtual vnl_unary_function<Return,Argument>* Copy() const { return 0; }

  virtual ~vnl_unary_function() {}
};

#endif // vnl_unary_function_h_
