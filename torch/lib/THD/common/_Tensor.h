#pragma once

#include <initializer_list>
#include <vector>
#include <type_traits>

struct Tensor {
  using long_range = std::vector<long>;

  Tensor() {};
  Tensor(const Tensor& other) = delete;
  Tensor(Tensor&& other) = delete;
  virtual ~Tensor() {};

  virtual int nDim() const = 0;
  virtual long_range sizes() const = 0;
  virtual long_range strides() const = 0;
  virtual const long* rawSizes() const = 0;
  virtual const long* rawStrides() const = 0;
  virtual size_t storageOffset() const = 0;
  virtual size_t elementSize() const = 0;
  virtual void* data() = 0;
  virtual const void* data() const = 0;

  virtual Tensor& resize(const std::initializer_list<long>& new_size) = 0;
};

template<typename real>
struct TensorScalarInterface : public Tensor {
  using scalar_type = real;
  virtual TensorScalarInterface& fill(scalar_type value) = 0;
  virtual TensorScalarInterface& add(const Tensor& source, scalar_type salar) = 0;
};

using FloatTensor = TensorScalarInterface<double>;
using IntTensor = TensorScalarInterface<long long>;

template<typename real>
struct tensor_traits {
  using scalar_type = typename std::conditional<
    std::is_floating_point<real>::value,
    double,
    long long>::type;
  using interface_type = TensorScalarInterface<scalar_type>;
};