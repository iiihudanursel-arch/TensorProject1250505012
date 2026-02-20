#ifndef TENSOR_H
#define TENSOR_H

#include <stdint.h>
#include <stdlib.h>

typedef enum {
    TENSOR_FLOAT32,
    TENSOR_FLOAT16,
    TENSOR_INT8
} TensorType;

typedef union {
    float* f32;
    uint16_t* f16;
    int8_t* i8;
} TensorData;

typedef struct {
    TensorData data;
    size_t length;
    TensorType type;

    float scale;
    int8_t zero_point;
} Tensor;

Tensor tensor_create(size_t length, TensorType type);
void tensor_free(Tensor* t);
void tensor_print(Tensor* t);

void tensor_quantize_f32_to_i8(Tensor* src, Tensor* dst, float scale, int8_t zero_point);
void tensor_dequantize_i8_to_f32(Tensor* src, Tensor* dst);

uint16_t float32_to_float16(float value);
float float16_to_float32(uint16_t value);

#endif
