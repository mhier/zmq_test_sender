#include "doocs/printtostderr.h"
#include <stdio.h>
#include "eq_zmq_test.h"
#include "eq_errors.h"
#include "eq_fct_errors.h"
#include <assert.h>
#include <sys/resource.h>
#include <boost/make_shared.hpp>
#include <istream>
#include <ostream>

using namespace std;



/******************************************************************************************************************/

EqFctZmqTest::EqFctZmqTest() : EqFct("LOCATION") {
}

/******************************************************************************************************************/

void EqFctZmqTest::post_init() {
    fast.set_mode(DMSG_EN);
    slow.set_mode(DMSG_EN);
    once.set_mode(DMSG_EN);
}

/******************************************************************************************************************/

void EqFctZmqTest::update() {
    dmsg_info_t db;
    memset (&db, 0, sizeof (db));

    auto now = doocs::Timestamp::now();
    db.sec   = now.get_seconds_and_microseconds_since_epoch().seconds;
    db.usec  = now.get_seconds_and_microseconds_since_epoch().microseconds;
    db.ident = 10000+counter;
    db.stat = 0;
    dmsg_error(&db, 0);

    if(counter == 0) {
       once.set_value(42);
       once.send(&db);
    }

    if(counter % 60000 == 0) {
        slow.set_value(counter);
        slow.send(&db);
    }

    fast.set_value(counter);
    fast.send(&db);

    ++counter;
}

/******************************************************************************************************************/
