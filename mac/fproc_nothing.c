/*
 * This file is part of the UWB stack for linux.
 *
 * Copyright (c) 2020-2021 Qorvo US, Inc.
 *
 * This software is provided under the GNU General Public License, version 2
 * (GPLv2), as well as under a Qorvo commercial license.
 *
 * You may choose to use this software under the terms of the GPLv2 License,
 * version 2 ("GPLv2"), as published by the Free Software Foundation.
 * You should have received a copy of the GPLv2 along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 *
 * This program is distributed under the GPLv2 in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GPLv2 for more
 * details.
 *
 * If you cannot meet the requirements of the GPLv2, you may not use this
 * software for any purpose without first obtaining a commercial license from
 * Qorvo. Please contact Qorvo to inquire about licensing terms.
 */

#include "mcps802154_i.h"
#include "llhw-ops.h"

static void mcps802154_fproc_nothing_access(struct mcps802154_local *local)
{
	mcps802154_fproc_access_done(local);
	mcps802154_fproc_access_now(local);
}

static const struct mcps802154_fproc_state mcps802154_fproc_nothing = {
	.name = "nothing",
	.timer_expired = mcps802154_fproc_nothing_access,
	.schedule_change = mcps802154_fproc_nothing_access,
};

int mcps802154_fproc_nothing_handle(struct mcps802154_local *local,
				    struct mcps802154_access *access)
{
	int r;

	r = llhw_idle(local, access->duration_dtu != 0,
		      access->timestamp_dtu + access->duration_dtu);
	if (r)
		return r;

	mcps802154_fproc_change_state(local, &mcps802154_fproc_nothing);

	return 0;
}
