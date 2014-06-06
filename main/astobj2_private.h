/*
 * astobj2 - replacement containers for asterisk data structures.
 *
 * Copyright (C) 2006 Marta Carbone, Luigi Rizzo - Univ. di Pisa, Italy
 *
 * See http://www.asterisk.org for more information about
 * the Asterisk project. Please do not directly contact
 * any of the maintainers of this project for assistance;
 * the project provides a web site, mailing lists and IRC
 * channels for your use.
 *
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */

/*! \file
 *
 * \brief Common, private definitions for astobj2.
 *
 * \author Richard Mudgett <rmudgett@digium.com>
 */

#ifndef ASTOBJ2_PRIVATE_H_
#define ASTOBJ2_PRIVATE_H_

#include "asterisk/astobj2.h"

#if defined(TEST_FRAMEWORK)
/* We are building with the test framework enabled so enable AO2 debug tests as well. */
#define AO2_DEBUG 1
#endif	/* defined(TEST_FRAMEWORK) */

#if defined(AST_DEVMODE)
#define AO2_DEVMODE_STAT(stat)	stat
#else
#define AO2_DEVMODE_STAT(stat)
#endif	/* defined(AST_DEVMODE) */

#ifdef AO2_DEBUG
struct ao2_stats {
	volatile int total_objects;
	volatile int total_mem;
	volatile int total_containers;
	volatile int total_refs;
	volatile int total_locked;
};
extern struct ao2_stats ao2;
#endif

int is_ao2_object(void *user_data);
enum ao2_lock_req __adjust_lock(void *user_data, enum ao2_lock_req lock_how, int keep_stronger);

#endif /* ASTOBJ2_PRIVATE_H_ */
