#include "tensor.h"
#include <stdio.h>

int main() {

    printf("=== FLOAT32 Tensor ===\n");

    Tensor input = tensor_create(5, TENSOR_FLOAT32);

    input.data.f32[0] = 0.12f;
    input.data.f32[1] = -0.45f;
    input.data.f32[2] = 1.20f;
    input.data.f32[3] = 0.33f;
    input.data.f32[4] = -0.78f;

    tensor_print(&input);

    printf("\nMemory Usage Float32: %zu bytes\n",
           input.length * sizeof(float));

    printf("\n=== Quantized INT8 Tensor ===\n");

    Tensor q = tensor_create(5, TENSOR_INT8);

    tensor_quantize_f32_to_i8(&input, &q, 0.01f, 0);

    tensor_print(&q);

    printf("\nMemory Usage INT8: %zu bytes\n",
           q.length * sizeof(int8_t));

    printf("\n=== Dequantized Back to FLOAT32 ===\n");

    Tensor deq = tensor_create(5, TENSOR_FLOAT32);

    tensor_dequantize_i8_to_f32(&q, &deq);

    tensor_print(&deq);

    tensor_free(&input);
    tensor_free(&q);
    tensor_free(&deq);

    return 0;
}