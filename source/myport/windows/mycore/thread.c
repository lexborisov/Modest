/*
 Copyright (C) 2015-2017 Alexander Borisov
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 
 Author: lex.borisov@gmail.com (Alexander Borisov)
*/

#include "mycore/mythread.h"

#ifndef MyCORE_BUILD_WITHOUT_THREADS
/***********************************************************************************
 *
 * For Windows
 *
 ***********************************************************************************/
mystatus_t mycore_thread_create(mythread_t *mythread, mythread_list_t *thr, void *work_func)
{
    thr->pth = CreateThread(NULL,                   // default security attributes
                            0,                      // use default stack size
                            work_func,              // thread function name
                            &thr->data,             // argument to thread function
                            0,                      // use default creation flags
                            NULL);                  // returns the thread identifier
    
    
    return MyCORE_STATUS_OK;
}

mystatus_t mycore_thread_join(mythread_t *mythread, mythread_list_t *thr)
{
    WaitForSingleObject(thr->pth, INFINITE);
    
    return MyCORE_STATUS_OK;
}

mystatus_t mycore_thread_cancel(mythread_t *mythread, mythread_list_t *thr)
{
    TerminateThread(thr->pth, 0);
    
    return MyCORE_STATUS_OK;
}

mystatus_t mycore_thread_attr_init(mythread_t *mythread)
{
    return MyCORE_STATUS_OK;
}

mystatus_t mycore_thread_attr_clean(mythread_t *mythread)
{
    return MyCORE_STATUS_OK;
}

mystatus_t mycore_thread_attr_destroy(mythread_t *mythread)
{
    return MyCORE_STATUS_OK;
}

mystatus_t mycore_hread_mutex_create(mythread_t *mythread, mythread_context_t *ctx, size_t prefix_id)
{
    ctx->mutex = CreateSemaphore(NULL, 0, 1, NULL);
    
    return MyCORE_STATUS_OK;
}

mystatus_t mycore_hread_mutex_post(mythread_t *mythread, mythread_context_t *ctx)
{
    ReleaseSemaphore(ctx->mutex, 1, NULL);
    
    return MyCORE_STATUS_OK;
}

mystatus_t mycore_hread_mutex_wait(mythread_t *mythread, mythread_context_t *ctx)
{
    WaitForSingleObject(ctx->mutex, INFINITE);
    
    return MyCORE_STATUS_OK;
}

mystatus_t mycore_hread_mutex_try_wait(mythread_t *mythread, mythread_context_t *ctx)
{
    return MyCORE_STATUS_OK;
}

mystatus_t mycore_hread_mutex_close(mythread_t *mythread, mythread_context_t *ctx)
{
    CloseHandle(ctx->mutex);
    
    return MyCORE_STATUS_OK;
}

void mycore_thread_nanosleep(const struct timespec *tomeout)
{
    Sleep(0);
}

#endif
