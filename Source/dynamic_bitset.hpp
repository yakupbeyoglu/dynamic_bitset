

#ifndef DYNAMIC_BITSET_H_
#define DYNAMIC_BITSET_H_
#include <algorithm>
#include <cmath>
#include <cstring>
#include <initializer_list>
#include <ostream>
#include <vector>

/**
 * @brief A dynamic bitset implementation that can be resized at runtime.
 *
 * The dynamic_bitset class provides a simple implementation of a bitset that
 * can be resized at runtime. It supports all the basic bit operations, such as
 * AND, OR, NOT, and XOR, as well as various other functions such as reverse,
 * to_string, and to_ulong.
 *
 * @tparam N The default size of the bitset. If no size is specified, the bitset
 * will be empty and ready for dynamic usage.
 */

template <std::size_t N = 0> class dynamic_bitset {
public:
  /**
   * @brief Default constructor that initializes the bitset with the default
   * size.
   */
  dynamic_bitset() : bits_(N) {}

  /**
   * @brief Constructor that initializes the bitset with a given integer value.
   *
   * @param value The integer value to initialize the bitset with.
   */
  dynamic_bitset(int value) : bits_(N) {
    auto binary = int_to_binary(value);
    int number_of_padding = bits_.size() - binary.size();
    add_padding(binary, number_of_padding);
    bits_ = std::move(binary);
  }

  /**
   * @brief Constructor that initializes the bitset with a vector of bools.
   *
   * @param binaries The vector of bools to initialize the bitset with.
   */
  dynamic_bitset(std::vector<bool> binaries) : bits_(N) {
    int number_of_padding = bits_.size() - binaries.size();
    add_padding(binaries, number_of_padding);
    bits_ = std::move(binaries);
  }

  /**
   * @brief Constructor that initializes the bitset with an initializer list of
   * bools.
   *
   * @param binaries The initializer list of bools to initialize the bitset
   * with.
   */
  dynamic_bitset(std::initializer_list<bool> binaries) : bits_(N) {
    int number_of_padding = bits_.size() - binaries.size();
    bits_ = std::move(binaries);
    add_padding(bits_, number_of_padding);
  }

  /**
   * @brief Constructor that initializes the bitset with a string of binary
   * digits.
   *
   * @param binary_string The string of binary digits to initialize the bitset
   * with.
   */
  dynamic_bitset(const std::string &binary_string) : bits_(N) {
    bits_ = std::move(string_to_bitset(binary_string));
  }

  /**
   * @brief Constructor that initializes the bitset with a C-style string of
   * binary digits.
   *
   * @param binary The C-style string of binary digits to initialize the bitset
   * with.
   */
  dynamic_bitset(const char *binary) : bits_(N) {
    int number_of_padding = bits_.size() - strlen(binary);
    std::vector<bool> binaries;

    while (*binary != '\0')
      binaries.emplace_back(*binary++ == '1');

    add_padding(binaries, number_of_padding);
    bits_ = std::move(binaries);
  }

  /**
   * @brief Destructor for dynamic_bitset.
   */
  ~dynamic_bitset() {}

  /**
   * @brief Delete the copy constructor for dynamic_bitset.
   */
  dynamic_bitset(const dynamic_bitset &) = delete;

  /**
   * @brief Delete the copy assignment operator for dynamic_bitset.
   */
  dynamic_bitset &operator=(const dynamic_bitset &) = delete;

  /**
   * @brief Move constructor for dynamic_bitset.
   * @param other The dynamic_bitset object to move from.
   */
  dynamic_bitset(dynamic_bitset &&other) : bits_(std::move(other.bits_)) {}

  /**
   * @brief Move assignment operator for dynamic_bitset.
   * @param other The dynamic_bitset object to move from.
   * @return A reference to the dynamic_bitset object after the move.
   */
  dynamic_bitset &operator=(dynamic_bitset &&other) {
    if (this != &other) {
      bits_ = std::move(other.bits_);
    }
    return *this;
  }

  /**
   * @brief Assignment operator to assign a std::vector<bool> to dynamic_bitset.
   * @param binaries The std::vector<bool> to assign.
   * @return A reference to the dynamic_bitset object after the assignment.
   */

  dynamic_bitset &operator=(const std::vector<bool> &binaries) {
    int number_of_padding = bits_.size() - binaries.size();
    bits_ = std::move(binaries);
    add_padding(bits_, number_of_padding);
    return *this;
  }

  /**
   * @brief Reverse the bits in dynamic_bitset.
   * @return A reference to the dynamic_bitset object after the reverse
   * operation.
   */
  dynamic_bitset &reverse() {
    std::reverse(std::begin(bits_), std::end(bits_));
    return *this;
  }

  /**
   * @brief Get the underlying std::vector<bool> object.
   * @return A const reference to the std::vector<bool> object.
   */

  const std::vector<bool> &get() const { return bits_; }

  /**
   * @brief Get the value of a bit at a given index.
   * @param index The index of the bit.
   * @return The value of the bit at the given index.
   */
  bool operator[](std::size_t index) const { return bits_.at(index); }

  /**
   * @brief Check if all bits in dynamic_bitset are true.
   * @return True if all bits are true, false otherwise.
   */
  bool all() const {
    return std::all_of(std::begin(bits_), std::end(bits_),
                       [](bool b) { return b; });
  }

  /**
   * @brief Check if any bit in dynamic_bitset is true.
   * @return True if any bit is true, false otherwise.
   */
  bool any() const {
    return std::any_of(std::begin(bits_), std::end(bits_),
                       [](bool b) { return b; });
  }

  /**
   * @brief Check if none of the bits in dynamic_bitset are true.
   * @return True if none of the bits are true, false otherwise.
   */
  bool none() const {
    return std::none_of(std::begin(bits_), std::end(bits_),
                        [](bool b) { return b; });
  }

  /**
   * @brief Return reference bit on the given index
   * @return Reference bit on the given index
   */
  inline std::vector<bool>::reference operator[](std::size_t index) {
    return bits_.at(index);
  }

  /**
   * @brief Return size of the bitset
   * @return sizse of bitset, if empty return 0
   */
  constexpr std::size_t size() const { return bits_.size(); }

  /**
   * @brief Set all value of the bitset
   * @return Return object itself
   */
  dynamic_bitset &set(bool value) {
    std::fill(std::begin(bits_), std::end(bits_), value);
    return *this;
  }

  /**
   * @brief Set all value to 0
   * @return Return object itself
   */
  inline dynamic_bitset &reset() { return set(false); }

  /**
   * @brief convert bitset to string bitset
   * @return Return string
   */
  std::string to_string() const {
    std::string str;
    for (const auto &bit : bits_)
      str.push_back(bit == true ? '1' : '0');

    return str;
  }

  /**
   * @brief string casting operator, return bitset to string
   * @return Return string
   */
  operator std::string() const { return to_string(); }

  /**
   * @brief bitset to std::size_t
   * @return return std::size_t, max possible of value
   */

  std::size_t to_ulong() const {
    std::size_t value = 0;
    std::size_t power = 1;
    for (auto it = bits_.rbegin(); it != bits_.rend(); ++it) {
      if (*it)
        value += power;
      power *= 2;
    }
    return value;
  }

  /**
   * @brief casting operator of std::size_t
   * @return return std::size_t, max possible of value
   */
  operator std::size_t() const { return to_ulong(); }

  /**
   * @brief casting operator of unsigned long
   * @return return std::size_t, max possible value
   */
  operator unsigned long const() {
    return static_cast<unsigned long>(to_ulong());
  }

  /**
   * @brief casting operator of unsigned long long
   * @return return std::size_t, max possible value
   */

  operator unsigned long long const() {
    return static_cast<unsigned long>(to_ulong());
  }

  /**
   * @brief and operator between two dynamic_bitset
   * @return return new dynamic_bitset
   */

  dynamic_bitset operator&(const dynamic_bitset &other) const {
    std::size_t size = std::min(bits_.size(), other.size());
    std::vector<bool> set;
    for (int i = 0; i < size; ++i)
      set.emplace_back(other[i] && bits_[i]);
    return dynamic_bitset(set);
  }

  /**
   * @brief and operator between two dynamic_bitset and change orginal set
   * @return dynamic_bitset itself
   */

  dynamic_bitset &operator&=(const dynamic_bitset &other) {
    std::size_t size = std::min(bits_.size(), other.size());
    for (int i = 0; i < size; ++i)
      bits_[i] = bits_[i] && other.bits_[i];
    return *this;
  }

  /**
   * @brief or operator between two dynamic_bitset
   * @return return new dynamic_bitset
   */
  dynamic_bitset operator|(const dynamic_bitset &other) const {
    std::size_t size = std::min(bits_.size(), other.size());
    std::vector<bool> set;
    for (int i = 0; i < size; ++i)
      set.emplace_back(other[i] || bits_[i]);
    return dynamic_bitset(set);
  }

  /**
   * @brief or operator between two dynamic_bitset and change orginal set
   * @return dynamic_bitset itself
   */

  dynamic_bitset &operator|=(const dynamic_bitset &other) {
    std::size_t size = std::min(bits_.size(), other.size());
    std::vector<bool> set;
    for (int i = 0; i < size; ++i)
      bits_[i] = bits_[i] || other.bits_[i];
    return *this;
  }

  /**
   * @brief xor operator between two dynamic_bitset
   * @return return new dynamic_bitset
   */
  dynamic_bitset operator^(const dynamic_bitset &other) const {
    std::size_t size = std::min(bits_.size(), other.size());
    std::vector<bool> set;
    for (int i = 0; i < size; ++i)
      set.emplace_back(other[i] ^ bits_[i]);
    return dynamic_bitset(set);
  }

  /**
   * @brief xor operator between two dynamic_bitset and change orginal set
   * @return dynamic_bitset itself
   */
  dynamic_bitset &operator^=(const dynamic_bitset &other) {
    std::size_t size = std::min(bits_.size(), other.size());
    std::vector<bool> set;
    for (int i = 0; i < size; ++i)
      bits_[i] = bits_[i] ^ other.bits_[i];
    return *this;
  }

  /**
   * @brief Left Shift operator
   * @tparam shift_amount, amount of the shift that will used for left shifting
   * @return dynamic_bitset itself
   */
  dynamic_bitset &operator<<=(std::size_t shift_amount) {
    if (shift_amount >= bits_.size())
      bits_.assign(bits_.size(), false);
    else {
      // shift all bits to left
      for (std::size_t i = 0; i < bits_.size(); ++i)
        bits_[i] = bits_[i + shift_amount];
      // fill shifted position
      for (std::size_t i = bits_.size() - shift_amount; i < bits_.size(); ++i)
        bits_[i] = false;
    }
    return *this;
  }

  /**
   * @brief Right Shift operator
   * @tparam shift_amount, amount of the shift that will used for right shifting
   * @return dynamic_bitset itself
   */
  dynamic_bitset &operator>>=(std::size_t shift_amount) {
    if (shift_amount >= bits_.size())
      bits_.assign(bits_.size(), false);
    else {
      // shift all bits to  right
      for (std::size_t i = bits_.size() - 1; i >= shift_amount; --i)
        bits_[i] = bits_[i - shift_amount];
      // fill shifted position
      for (std::size_t i = 0; i < shift_amount; ++i)
        bits_[i] = false;
    }
    return *this;
  }

  /**
   * @brief begin iterator
   * @return dynamic_bitset begin itreator
   */
  std::vector<bool>::iterator begin() { return bits_.begin(); }

  /**
   * @brief begin iterator
   * @return dynamic_bitset begin itreator
   */
  std::vector<bool>::iterator end() { return bits_.end(); }

  /**
   * @brief ostream operator to print dynamic_bitset
   * @return ostream
   */

  friend std::ostream &operator<<(std::ostream &out,
                                  const dynamic_bitset &set) {
    for (const auto &bit : set.bits_) {
      out << bit;
    }
    return out;
  }

  /**
   * @brief istream operator to input of dynamic_bitset
   * @return istream
   */

  friend std::istream &operator>>(std::istream &input, dynamic_bitset &set) {
    std::string str;
    input >> str;
    set.bits_ = std::move(set.string_to_bitset(str));
    return input;
  }

private:
  /**
   * @brief Convert strign to binary bitset with using padding
   * @return none
   */

  std::vector<bool> string_to_bitset(const std::string &binary_string) {
    int number_of_padding = bits_.size() - binary_string.size();
    std::vector<bool> binaries;
    for (const char &c : binary_string)
      binaries.emplace_back(c == '1');
    add_padding(binaries, number_of_padding);
    return binaries;
  }

  /**
   * @brief Add padding bits (0) to given vector
   * @return none
   */
  void add_padding(std::vector<bool> &base, int number_of_padding) {
    for (int i = 0; i < number_of_padding; ++i)
      base.insert(base.begin(), 0);
  }

  /**
   * @brief Convert int to binary bitset
   * @return std::vector<bool>
   */
  std::vector<bool> int_to_binary(int value) {
    std::vector<bool> temp;
    while (value > 0) {
      temp.insert(temp.begin(), static_cast<bool>(value % 2));
      value /= 2;
    }
    if (temp.empty())
      temp.emplace_back(value);
    return temp;
  }

  std::vector<bool> bits_;
};

#endif
