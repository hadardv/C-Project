#pragma once

#ifndef MACROS_H_
#define MACROS_H_

#define RETURN_NULL(ptr) {if(!ptr) return NULL;}
#define RETURN_ZERO(ptr) {if(!ptr) return 0;}
#define COLSE_FILE_RETURN_ZERO(fp) {fclose(fp); return 0;}
#define RETURN_AND_FREE(ptr) {if(!ptr){ free(ptr) ; return 0;} }



#endif