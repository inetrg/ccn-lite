#ifndef CCNL_UTILS_H
#define CCNL_UTILS_H

#define free_2ptr_list(a,b)       ccnl_free(a), ccnl_free(b)
#define free_3ptr_list(a,b,c)     ccnl_free(a), ccnl_free(b), ccnl_free(c)
#define free_4ptr_list(a,b,c,d)   ccnl_free(a), ccnl_free(b), ccnl_free(c), ccnl_free(d);
#define free_5ptr_list(a,b,c,d,e) ccnl_free(a), ccnl_free(b), ccnl_free(c), ccnl_free(d), ccnl_free(e);
#define free_prefix(p)  do{ if(!p) break; ccnl_free(p->chunknum);  \
                free_4ptr_list(p->bytes,p->comp,p->complen,p); } while(0)
#define free_content(c) do{ /* free_prefix(c->name); */ free_packet(c->pkt); \
                        ccnl_free(c); } while(0)

#endif /* CCNL-UTILS_H */
