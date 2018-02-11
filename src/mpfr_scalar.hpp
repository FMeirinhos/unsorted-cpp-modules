//
//  mpfr_scalar.hpp
//
//  Created by Francisco Meirinhos on 06/01/17.
//

#ifndef mpfr_scalar_hpp
#define mpfr_scalar_hpp

#include <mpfr.h>

/*
 GNU Multiple Precision Floating-Point Reliably -- wrapped in a class
 */

class MPScalar;

// This is probably violating c++ standards, don't tell anyone
// _LIBCPP_BEGIN_NAMESPACE_STD
// template <> struct __libcpp_is_floating_point<MPScalar> : public true_type
// {}; _LIBCPP_END_NAMESPACE_STD

namespace mpfr {
// Rounding
mpfr_rnd_t rounding() { return mpfr_get_default_rounding_mode(); };

// Precision
mpfr_prec_t precision() { return mpfr_get_default_prec(); };
}; // namespace mpfr

class MPScalar {
public:
  /// Ctor
  MPScalar() { init(); };
  MPScalar(const double &a, mpfr_prec_t prec = mpfr::precision()) {
    init(prec);
    mpfr_set_d(pointer(), a, mpfr::rounding());
  }
  MPScalar(const MPScalar &a, mpfr_prec_t prec = mpfr::precision()) {
    assert(&a != this);

    init(prec);
    mpfr_set(pointer(), a.pointer(), mpfr::rounding());
  }

  /// Dtor
  ~MPScalar() {}

  /// Assign
  const MPScalar &operator=(const MPScalar &a) {
    mpfr_set(pointer(), a.pointer(), mpfr::rounding());
    return *this;
  }
  const MPScalar &operator=(MPScalar &&a) {
    mpfr_swap(pointer(), a.pointer());
    return *this;
  }
  const MPScalar &operator=(const double &a) {
    mpfr_set_d(pointer(), a, mpfr::rounding());
    return *this;
  }

  /// Addition
  const MPScalar &operator+=(const MPScalar &a) {
    mpfr_add(pointer(), pointer(), a.pointer(), mpfr::rounding());
    return *this;
  }
  const MPScalar &operator+=(const double &a) {
    mpfr_add_d(pointer(), pointer(), a, mpfr::rounding());
    return *this;
  }

  /// Subtraction
  const MPScalar &operator-=(const MPScalar &a) {
    mpfr_sub(pointer(), pointer(), a.pointer(), mpfr::rounding());
    return *this;
  }
  const MPScalar &operator-=(const double &a) {
    mpfr_sub_d(pointer(), pointer(), a, mpfr::rounding());
    return *this;
  }

  /// Multiplication
  const MPScalar &operator*=(const MPScalar &a) {
    mpfr_mul(pointer(), pointer(), a.pointer(), mpfr::rounding());
    return *this;
  }
  const MPScalar &operator*=(const double &a) {
    mpfr_mul_d(pointer(), pointer(), a, mpfr::rounding());
    return *this;
  }

  /// Division
  const MPScalar &operator/=(const MPScalar &a) {
    mpfr_div(pointer(), pointer(), a.pointer(), mpfr::rounding());
    return *this;
  }
  const MPScalar &operator/=(const double &a) {
    mpfr_div_d(pointer(), pointer(), a, mpfr::rounding());
    return *this;
  }

  // Return double
  explicit operator double() const {
    return mpfr_get_d(pointer(), mpfr::rounding());
  }

public:
  mpfr_ptr pointer() { return _mpfr_scalar; };

  mpfr_srcptr pointer() const { return _mpfr_scalar; };

  mpfr_sign_t sgn() const { return _mpfr_scalar->_mpfr_sign; };

  mpfr_exp_t exponent() const { return _mpfr_scalar->_mpfr_exp; };

  mpfr_prec_t precision() const { return _mpfr_scalar->_mpfr_prec; }

private:
  void init(mpfr_prec_t prec = mpfr::precision()) {
    mpfr_init2(_mpfr_scalar, prec);
  }

private:
  // Variable
  mpfr_t _mpfr_scalar;
};

// Get exponential e^{ _mpfr_scalar }
MPScalar exp(const MPScalar &a) {
  MPScalar _exp;
  mpfr_exp(_exp.pointer(), a.pointer(), mpfr::rounding());
  return _exp;
}

// Get logarithm \log{ _mpfr_scalar }
MPScalar log(const MPScalar &a) {
  MPScalar _log;
  mpfr_log(_log.pointer(), a.pointer(), mpfr::rounding());
  return _log;
}

MPScalar operator+(const MPScalar &a, const MPScalar &b) {
  return MPScalar(a) += b;
}
MPScalar operator-(const MPScalar &a, const MPScalar &b) {
  return MPScalar(a) -= b;
}
MPScalar operator*(const MPScalar &a, const MPScalar &b) {
  return MPScalar(a) *= b;
}
MPScalar operator/(const MPScalar &a, const MPScalar &b) {
  return MPScalar(a) /= b;
}

MPScalar operator+(const MPScalar &a, const double &b) {
  return MPScalar(a) += b;
}
MPScalar operator-(const MPScalar &a, const double &b) {
  return MPScalar(a) -= b;
}
MPScalar operator*(const MPScalar &a, const double &b) {
  return MPScalar(a) *= b;
}
MPScalar operator/(const MPScalar &a, const double &b) {
  return MPScalar(a) /= b;
}

#endif /* mpfr_scalar_hpp */
