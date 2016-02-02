/******************************************************************************
 * Copyright © 2014-2016 The SuperNET Developers.                             *
 *                                                                            *
 * See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at                  *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                                            *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * SuperNET software, including this file may be copied, modified, propagated *
 * or distributed except according to the terms contained in the LICENSE file *
 *                                                                            *
 * Removal or modification of this copyright notice is prohibited.            *
 *                                                                            *
 ******************************************************************************/

#define EXCHANGE_NAME "nxtae"
#define UPDATE nxtae ## _price
#define SUPPORTS nxtae ## _supports
#define SIGNPOST nxtae ## _signpost
#define TRADE nxtae ## _trade
#define ORDERSTATUS nxtae ## _orderstatus
#define CANCELORDER nxtae ## _cancelorder
#define OPENORDERS nxtae ## _openorders
#define TRADEHISTORY nxtae ## _tradehistory
#define BALANCES nxtae ## _balances
#define PARSEBALANCE nxtae ## _parsebalance
#define WITHDRAW nxtae ## _withdraw
#define CHECKBALANCE nxtae ## _checkbalance
#define ALLPAIRS nxtae ## _allpairs
#define FUNCS nxtae ## _funcs
#define BASERELS nxtae ## _baserels

static char *BASERELS[][2] = { {"btc","nxt"}, {"btc","btcd"}, {"btc","ltc"}, {"btc","vrc"}, {"btc","doge"} };
#include "exchange_supports.h"

double UPDATE(struct exchange_info *exchange,char *base,char *rel,struct exchange_quote *bidasks,int32_t maxdepth,double commission,cJSON *argjson,int32_t invert)
{
    double bid,ask,bids[64],asks[64],highs[64],lows[64]; int32_t numbids,numasks,c; char name[32];
    if ( fxcm_ensure() == 0 )
    {
        strcpy(name,base), strcat(name,rel), touppercase(name);
        if ( (c= strsearch(FXCM_contracts,num_FXCM,name)) >= 0 )
        {
            prices777_fxcm(bids,asks,highs,lows);
            numbids = numasks = 0;
            bid = exchange_setquote(bidasks,&numbids,&numasks,0,invert,bids[c],1,commission,0,(uint32_t)time(NULL),0);
            ask = exchange_setquote(bidasks,&numbids,&numasks,1,invert,asks[c],1,commission,0,(uint32_t)time(NULL),0);
            if ( bid > SMALLVAL && ask > SMALLVAL )
                return((bid + ask) * .5);
        }
    }
    return(0);
}

cJSON *SIGNPOST(void **cHandlep,int32_t dotrade,char **retstrp,struct exchange_info *exchange,char *payload,char *path)
{
    if ( retstrp != 0 )
        *retstrp = clonestr("{\"error\":\"nxtae is readonly data source\"}");
    return(cJSON_Parse("{}"));
}

char *PARSEBALANCE(struct exchange_info *exchange,double *balancep,char *coinstr,cJSON *argjson)
{
    return(clonestr("{\"error\":\"nxtae is readonly data source\"}"));
}

cJSON *BALANCES(struct exchange_info *exchange,cJSON *argjson)
{
    return(cJSON_Parse("{\"error\":\"nxtae is readonly data source\"}"));
}

uint64_t TRADE(int32_t dotrade,char **retstrp,struct exchange_info *exchange,char *base,char *rel,int32_t dir,double price,double volume,cJSON *argjson)
{
    return(0);
}

char *ORDERSTATUS(struct exchange_info *exchange,uint64_t quoteid,cJSON *argjson)
{
    return(clonestr("{\"error\":\"nxtae is readonly data source\"}"));
}

char *CANCELORDER(struct exchange_info *exchange,uint64_t quoteid,cJSON *argjson)
{
    return(clonestr("{\"error\":\"nxtae is readonly data source\"}"));
}

char *OPENORDERS(struct exchange_info *exchange,cJSON *argjson)
{
    return(clonestr("{\"error\":\"nxtae is readonly data source\"}"));
}

char *TRADEHISTORY(struct exchange_info *exchange,cJSON *argjson)
{
    return(clonestr("{\"error\":\"nxtae is readonly data source\"}"));
}

char *WITHDRAW(struct exchange_info *exchange,char *base,double amount,char *destaddr,cJSON *argjson)
{
    return(clonestr("{\"error\":\"nxtae is readonly data source\"}"));
}

struct exchange_funcs nxtae_funcs = EXCHANGE_FUNCS(nxtae,EXCHANGE_NAME);

#include "exchange_undefs.h"
