/* Copyright © 2018-2019 N. Van Bossuyt.                                      */
/* This code is licensed under the MIT License.                               */
/* See: LICENSE.md                                                            */

#include <string.h>

#include "kernel/memory.h"

#include "kernel/process.h"

static int PID = 1;

process_t *alloc_process(const char *name, bool user)
{
    process_t *process = MALLOC(process_t);

    if (process == NULL)
    {
        PANIC("Failed to allocated a new process.");
    }

    process->id = PID++;

    strncpy(process->name, name, MAX_PROCESS_NAMESIZE);
    process->user = user;
    process->threads = list();
    process->inbox = list();
    process->shared = list();

    if (user)
    {
        process->pdir = memory_alloc_pdir();
    }
    else
    {
        process->pdir = memory_kpdir();
    }

    sk_log(LOG_FINE, "Process '%s' with ID=%d allocated.", process->name, process->id);

    return process;
}

void process_delete(process_t* process)
{
    if (process->pdir != memory_kpdir())
    {
        memory_free_pdir(process->pdir);
    }

    if (list_any(process->threads))
    {
        PANIC("Process's threads-list isn't empty!");
    }
    else
    {
        list_delete(process->threads);
    }

    if (list_any(process->inbox  ))
    {
        PANIC("Process's inbox-list isn't empty!");
    }
    else
    {
        list_delete(process->inbox);
    }

    if (list_any(process->shared ))
    {
        PANIC("Process's shared-list isn't empty!");
    }
    else
    {
        list_delete(process->shared );
    }

    free(process);
}
