/* Copyright 2022 Google LLC
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
      http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "autoconf.h"
#include "krb5.h"

#define kMinInputLength 10
#define kMaxInputLength 5120

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) 
{//src/tests/misc/test_chpw_message.c

    if (Size < kMinInputLength || Size > kMaxInputLength){
        return 0;
    }

    char *msg;
    krb5_context context;

    krb5_init_context(&context);

    krb5_data DataInput;
    DataInput.magic = 0;
    DataInput.length = Size;
    DataInput.data = (char *)Data;

    krb5_chpw_message(context, &DataInput, &msg);

    free(msg);
    krb5_free_context(context);

    return 0;
}
