


#ifndef _AVL6211SF_H_
#define _AVL6211SF_H_



#include <linux/dvb/frontend.h>
#include "../../../media/dvb/dvb-core/dvb_frontend.h"
#include "../aml_dvb.h"


#define printf printk


struct avl6211_fe_config {
	int                   i2c_id;
	int                 reset_pin;
	int                 demod_addr;
	int                 tuner_addr;
	void 			  *i2c_adapter;
};


struct avl6211_state {
	struct avl6211_fe_config config;
	struct i2c_adapter *i2c;
	u32                 freq;
        fe_modulation_t     mode;
        u32                 symbol_rate;
        struct dvb_frontend fe;
};


#endif
