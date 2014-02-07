#ifndef ANTARES_LIB_CONTRIB_CEREBELLUM_IO_H
#define ANTARES_LIB_CONTRIB_CEREBELLUM_IO_H

/**
 * Cerebellum I/O system structures and functions
 *
 * Base idea:
 *      Every hardware module (hi-level, like DC engine, encoders,
 *      data storages and buses) is described as set of software 
 *      registers. Register is a piece of memory which contains 
 *      register data, size and read/write handlers (from driver).
 *
 *      Basic I/O API implements read and write functions only.
 *
 *      For debug purposes, use Antares console features (printk and
 *      other).
 */

/**
 * Description of register.
 *
 * There are some types of registers of different sizes.
 *
 *      1. 8-bit register;
 *      2. 16-bit register;
 *      3. 32-bit register;
 *      4. 64-bit register;
 *      5. String register (with char * type of data)
 *
 * For each size, there are signed and unsigned variants.
 */

/**
 * To decrease memory size, there are macroses to read and write registers;
 * also, if you need, you can compile set of functions to access registers.
 */
#define CREG_READ(reg, var) do { var = reg->data; if (reg->read) reg->read(reg); } while (0)
#define CREG_WRITE(reg, value) do { reg->data = value; if (reg->write) reg->write(reg); } while (0)

#include <stdint.h>

/* For generation purposes only; C preprocessor don't do it the right way

#define CEREBELLUM_REGISTER_TYPEDEF(base_type, name) \
        struct _cerebellum_reg_struct_##name {  %\
                base_type## data; %\
                void (*read) (struct _cerebellum_reg_struct_##name *); %\
                void (*write) (struct _cerebellum_reg_struct_##name *); %\
        }; %\
        typedef struct _cerebellum_reg_struct_##name *creg_##name; %\
        typedef void (*creg_handler_##name) (creg_##name)

*/


/**
 * 8-bit registers types
 */

struct _cerebellum_reg_struct_u8 { 
        uint8_t data; 
        void (*read) (struct _cerebellum_reg_struct_u8 *); 
        void (*write) (struct _cerebellum_reg_struct_u8 *); 
}; 
typedef struct _cerebellum_reg_struct_u8 *creg_u8; 
typedef void (*creg_handler_u8) (creg_u8);

struct _cerebellum_reg_struct_s8 { 
        int8_t data; 
        void (*read) (struct _cerebellum_reg_struct_s8 *); 
        void (*write) (struct _cerebellum_reg_struct_s8 *); 
}; 
typedef struct _cerebellum_reg_struct_s8 *creg_s8; 
typedef void (*creg_handler_s8) (creg_s8);

/**
 * 16-bit register types
 */

struct _cerebellum_reg_struct_u16 { 
        uint16_t data; 
        void (*read) (struct _cerebellum_reg_struct_u16 *); 
        void (*write) (struct _cerebellum_reg_struct_u16 *); 
}; 
typedef struct _cerebellum_reg_struct_u16 *creg_u16; 
typedef void (*creg_handler_u16) (creg_u16);

struct _cerebellum_reg_struct_s16 { 
        int16_t data; 
        void (*read) (struct _cerebellum_reg_struct_s16 *); 
        void (*write) (struct _cerebellum_reg_struct_s16 *); 
}; 
typedef struct _cerebellum_reg_struct_s16 *creg_s16; 
typedef void (*creg_handler_s16) (creg_s16);


/**
 * 32-bit register types
 */

struct _cerebellum_reg_struct_u32 { 
        uint32_t data; 
        void (*read) (struct _cerebellum_reg_struct_u32 *); 
        void (*write) (struct _cerebellum_reg_struct_u32 *); 
}; 
typedef struct _cerebellum_reg_struct_u32 *creg_u32; 
typedef void (*creg_handler_u32) (creg_u32);

struct _cerebellum_reg_struct_s32 { 
        int32_t data; 
        void (*read) (struct _cerebellum_reg_struct_s32 *); 
        void (*write) (struct _cerebellum_reg_struct_s32 *); 
}; 
typedef struct _cerebellum_reg_struct_s32 *creg_s32; 
typedef void (*creg_handler_s32) (creg_s32);


/**
 * 64-bit register types
 */

struct _cerebellum_reg_struct_u64 {
        uint64_t data; 
        void (*read) (struct _cerebellum_reg_struct_u64 *); 
        void (*write) (struct _cerebellum_reg_struct_u64 *); 
}; 
typedef struct _cerebellum_reg_struct_u64 *creg_u64; 
typedef void (*creg_handler_u64) (creg_u64);

struct _cerebellum_reg_struct_s64 { 
        int64_t data; 
        void (*read) (struct _cerebellum_reg_struct_s64 *); 
        void (*write) (struct _cerebellum_reg_struct_s64 *); 
}; 
typedef struct _cerebellum_reg_struct_s64 *creg_s64; 
typedef void (*creg_handler_s64) (creg_s64);

/**
 * Float register types
 */

struct _cerebellum_reg_struct_float {
        float data; 
        void (*read) (struct _cerebellum_reg_struct_u64 *); 
        void (*write) (struct _cerebellum_reg_struct_u64 *); 
}; 
typedef struct _cerebellum_reg_struct_float *creg_float; 
typedef void (*creg_handler_float) (creg_float);

/**
 * String register type
 */

struct _cerebellum_reg_struct_str { 
        char *data; 
        void (*read) (struct _cerebellum_reg_struct_str *); 
        void (*write) (struct _cerebellum_reg_struct_str *); 
}; 
typedef struct _cerebellum_reg_struct_str *creg_str; 
typedef void (*creg_handler_str) (creg_str);

#endif
