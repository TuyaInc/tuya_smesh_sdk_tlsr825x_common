/*
 * ty_mesh_common.h
 *
 *  Created on: 2020-08-11
 *      Author: Joey
 */

#ifndef __TY_MESH_COMMON_H
#define __TY_MESH_COMMON_H



void tuya_mesh_app_init(void);

void tuya_mesh_main_run(void);

void tuya_mesh_state_callback(mesh_state_t stat);

void tuya_mesh_factory_reset(void);

extern void mesh_app_init(void);
extern void mesh_main_run(void);
extern void mesh_factory_reset(void);
extern void mesh_state_callback(mesh_state_t stat);





#endif
