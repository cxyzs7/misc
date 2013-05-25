#ifndef _MOVING_AVERAGE_H_
#define _MOVING_AVERAGE_H_

#include <list>

//! computes a (weighted) running average for values
template <typename T>
class moving_average
{
public:
  moving_average(size_t _size):
      m_cur_size(0), m_max_size(_size), m_run_sum(), m_weight_sum(), m_run_weighted_sum()
  {
  }
  void add_val(const T& val) {
    m_vals.push_back(val);
    // already full
    if (m_cur_size == m_max_size) {
      // handle weighted sum first
      m_run_weighted_sum -= m_run_sum;
      m_run_sum -= *m_vals.begin();
      m_vals.pop_front();
    } else {
      m_cur_size++;
      m_weight_sum += m_cur_size;
    }
    m_run_weighted_sum += val*m_cur_size;
    m_run_sum += val;
  }

  double get_average() const {
    if (m_cur_size) {
      return static_cast<double>(m_run_sum)/m_cur_size;
    } else {
      return 0.0;
    }
  }

  //! weight more recent values with larger weight
  double get_linear_weighted_avgerage() const {
    if (m_cur_size) {
      return static_cast<double>(m_run_weighted_sum)/m_weight_sum;
    } else {
      return 0.0;
    }
  }

  size_t size() const {
    return m_cur_size;
  }

  void clear() {
    m_vals.clear();
    m_cur_size = 0;
    m_run_sum = T();
    m_weight_sum = T();
    m_run_weighted_sum = T();
  }

public:
  std::list<T>    m_vals;
  size_t          m_cur_size;
  size_t          m_max_size;
  T               m_run_sum;
  T               m_weight_sum;
  T               m_run_weighted_sum;
};

#endif