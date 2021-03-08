#ifndef eq_vs_stat_h
#define eq_vs_stat_h

#include <vector>
#include <time.h>
#include "d_fct.h"
#include "eq_fct.h"
#include "eq_client.h"
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <ChimeraTK/cppext/future_queue.hpp>
#include <boost/shared_ptr.hpp>

/******************************************************************************************************************/

class EqFctZmqTest : public EqFct {
 public:
  EqFctZmqTest();

  void update() override;
  void post_init() override;
  int fct_code() override { return 10; }

  D_int fast{this, "FAST"};
  D_int slow{this, "SLOW"};
  D_int once{this, "ONCE"};

  size_t counter{0};

};

#endif
