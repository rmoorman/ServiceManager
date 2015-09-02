#ifndef _S16_H_
#define _S16_H_

#include "uthash.h"
#include "repositoryd_rpc.h"

typedef struct svc_s
{
    unsigned long id;
    char * name;
    struct property_s * properties;
    struct svc_instance_s * instances;

    UT_hash_handle hh;
} svc_t;

typedef struct svc_instance_s
{
    unsigned long id;
    char * name;
    struct property_s * properties;

    unsigned int svc_id;
    UT_hash_handle hh;
} svc_instance_t;

typedef struct property_s
{
    unsigned long id; /* uthash key */
    char * name;      /* key, but not uthash key */
    pval_t value;

    property_parent_type_t parent_type;
    unsigned int parent_id;
    UT_hash_handle hh;
} property_t;

#define gen_find_id_wrapper_proto(type)                                        \
    type##_t * type##_find_id (type##_t * box, unsigned long * keyptr);

#define gen_find_name_wrapper_proto(type)                                      \
    type##_t * type##_find_name (type##_t * box, char const * name);

gen_find_id_wrapper_proto (svc);
gen_find_name_wrapper_proto (svc);

gen_find_id_wrapper_proto (property);
gen_find_name_wrapper_proto (property);

void svc_object_set_property_string (svc_t * Svc, const char * key,
                                     const char * value);
void svc_object_set_property_int (svc_t * Svc, const char * key, long value);

void destroy_property (property_t * delProperty);
void destroy_properties_list (property_t * box);
void destroy_instance (svc_instance_t * delInstance);
void destroy_svc (svc_t * delSvc);
void destroy_svcs_list (svc_t * box);

#define DestroyPropIfExists(list, name)                                        \
    property_t * Prop = property_find_name (list, name);                       \
    if (Prop)                                                                  \
    {                                                                          \
        HASH_DEL (list, Prop);                                                 \
        destroy_property (Prop);                                               \
    }

#endif
