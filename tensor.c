#include "tensor.h"
#include <stdio.h>
#include <math.h>

static int8_t clamp_int8(int value) {
    if (value > 127) return 127;
    if (value < -128) return -128;
    return (int8_t)value;
}

Tensor tensor_create(size_t length, TensorType type) {
    Tensor t;
    t.length = length;
    t.type = type;
    t.scale = 1.0f;
    t.zero_point = 0;

    switch(type) {
        case TENSOR_FLOAT32:
            t.data.f32 = (float*)malloc(length * sizeof(float));
            break;
        case TENSOR_FLOAT16:
            t.data.f16 = (uint16_t*)malloc(length * sizeof(uint16_t));
            break;
        case TENSOR_INT8:
            t.data.i8 = (int8_t*)malloc(length * sizeof(int8_t));
            break;
    }

    return t;
}

void tensor_free(Tensor* t) {
    if (!t) return;

    switch(t->type) {
        case TENSOR_FLOAT32:
            free(t->data.f32);
            break;
        case TENSOR_FLOAT16:
            free(t->data.f16);
            break;
        case TENSOR_INT8:
            free(t->data.i8);
            break;
    }

    t->data.f32 = NULL;
}

void tensor_print(Tensor* t) {
    printf("Tensor Type: %d | Length: %zu\n", t->type, t->length);

    for (size_t i = 0; i < t->length; i++) {
        if (t->type == TENSOR_FLOAT32)
            printf("[%zu] %f\n", i, t->data.f32[i]);
        else if (t->type == TENSOR_INT8)
            printf("[%zu] %d\n", i, t->data.i8[i]);
    }
}

void tensor_quantize_f32_to_i8(Tensor* src, Tensor* dst, float scale, int8_t zero_point) {

    if (src->type != TENSOR_FLOAT32 || dst->type != TENSOR_INT8)
        return;

    dst->scale = scale;
    dst->zero_point = zero_point;

    for (size_t i = 0; i < src->length; i++) {
        float real_val = src->data.f32[i];
        int quantized = (int)round(real_val / scale) + zero_point;
        dst->data.i8[i] = clamp_int8(quantized);
    }
}

void tensor_dequantize_i8_to_f32(Tensor* src, Tensor* dst) {

    if (src->type != TENSOR_INT8 || dst->type != TENSOR_FLOAT32)
        return;

    for (size_t i = 0; i < src->length; i++) {
        dst->data.f32[i] =
            (src->data.i8[i] - src->zero_point) * src->scale;
    }
}