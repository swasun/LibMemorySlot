/******************************************************************************
* Copyright (C) 2018 by Charly Lamothe                                        *
*                                                                             *
* This file is part of LibMemorySlot.                                         *
*                                                                             *
*   LibMemorySlot is free software: you can redistribute it and/or modify     *
*   it under the terms of the GNU General Public License as published by      *
*   the Free Software Foundation, either version 3 of the License, or         *
*   (at your option) any later version.                                       *
*                                                                             *
*   LibMemorySlot is distributed in the hope that it will be useful,          *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of            *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
*   GNU General Public License for more details.                              *
*                                                                             *
*   You should have received a copy of the GNU General Public License         *
*   along with LibMemorySlot.  If not, see <http://www.gnu.org/licenses/>.    *
*******************************************************************************/

#include <ms/ms.h>

#include <ei/ei.h>

#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define SLOT_ID 100

int main() {
	ms_slot *slot;
	size_t i;
	char *string;

	ei_init();

	slot = NULL;
	string = NULL;

	ei_logger_info("Check if slot exist...");
	if (!ms_slot_exist_from_memory(SLOT_ID)) {
		if (ei_stacktrace_is_filled()) {
			ei_stacktrace_push_msg("Failed to check if slot exist");
			goto clean_up;
		}
		else {
			ei_logger_error("Specified slot doesn't exist");
			goto clean_up;
		}
	}
	ei_logger_info("Slot exist");

	ei_logger_info("Loading slot id %d...", SLOT_ID);
	if (!(slot = ms_slot_load_from_memory(SLOT_ID))) {
		ei_stacktrace_push_msg("Failed to load slot %d", SLOT_ID);
		goto clean_up;
	}
	ei_logger_info("Slot of size %ld loaded", slot->size);
	
	ei_safe_alloc(string, char, slot->size + 1);
	memcpy(string, slot->data, slot->size * sizeof(char));
	ei_logger_info("Content of the slot: %s", string);
	ei_safe_free(string);

	ei_logger_info("Searching slot id with retrieved data...");
	if (ms_slot_find_id_from_memory(slot) != SLOT_ID) {
		ei_stacktrace_push_msg("Failed to find id");
		goto clean_up;
	}
	ei_logger_info("Found the same slot id");

clean_up:
	ms_slot_destroy(slot);
	if (ei_stacktrace_is_filled()) {
		ei_logger_stacktrace("Stacktrace is filled with following error(s):");
	}
	ei_uninit();
	return 0;
}
