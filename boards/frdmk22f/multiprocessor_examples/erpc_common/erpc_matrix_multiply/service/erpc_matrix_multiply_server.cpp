/*
 * Generated by erpcgen 1.3.0 on Mon Sep  5 16:12:47 2016.
 *
 * AUTOGENERATED - DO NOT EDIT
 */

#include "erpc_matrix_multiply_server.h"
#include <new>
#include "erpc_port.h"

using namespace erpc;
#if !(__embedded_cplusplus)
using namespace std;
#endif

// Constant variable definitions
const int32_t matrix_size = 5;


// Call the correct server shim based on method unique ID.
erpc_status_t MatrixMultiplyService_service::handleInvocation(uint32_t methodId, uint32_t sequence, Codec * in, Codec * out)
{
    switch (methodId)
    {
        case kMatrixMultiplyService_erpcMatrixMultiply_id:
            return erpcMatrixMultiply_shim(in, out, sequence);

        default:
            return kErpcStatus_InvalidArgument;
    }
}

// Server shim for erpcMatrixMultiply of MatrixMultiplyService interface.
erpc_status_t MatrixMultiplyService_service::erpcMatrixMultiply_shim(Codec * in, Codec * out, uint32_t sequence)
{
    erpc_status_t err = kErpcStatus_Success;
    Matrix *matrix1 = NULL;
    matrix1 = (Matrix *) erpc_malloc(sizeof(Matrix));
    if (matrix1 == NULL)
    {
        err = kErpcStatus_MemoryError;
    }
    Matrix *matrix2 = NULL;
    matrix2 = (Matrix *) erpc_malloc(sizeof(Matrix));
    if (matrix2 == NULL)
    {
        err = kErpcStatus_MemoryError;
    }
    Matrix *result_matrix = NULL;

    // startReadMessage() was already called before this shim was invoked.
    if (!err)
    {
        err = in->startReadStruct();
    }

    if (!err)
    {
        for (uint32_t arrayCount1 = 0; arrayCount1 < 5; ++arrayCount1)
        {
            for (uint32_t arrayCount2 = 0; arrayCount2 < 5; ++arrayCount2)
            {
                if (!err)
                {
                    err = in->read(&(*matrix1)[arrayCount1][arrayCount2]);
                }
                else
                {
                    break;
                }
            }
        }
    }


    if (!err)
    {
        for (uint32_t arrayCount1 = 0; arrayCount1 < 5; ++arrayCount1)
        {
            for (uint32_t arrayCount2 = 0; arrayCount2 < 5; ++arrayCount2)
            {
                if (!err)
                {
                    err = in->read(&(*matrix2)[arrayCount1][arrayCount2]);
                }
                else
                {
                    break;
                }
            }
        }
    }

    if (!err)
    {
        err = in->endReadStruct();
    }

    if (!err)
    {
        err = in->endReadMessage();
    }


    result_matrix = (Matrix *) erpc_malloc(sizeof(Matrix));
if (result_matrix == NULL)
{
    err = kErpcStatus_MemoryError;
}
    // Invoke the actual served function.
    if (!err)
    {
        erpcMatrixMultiply(matrix1, matrix2, result_matrix);
    }


    // Build response message.
    if (!err)
    {
        err = out->startWriteMessage(kReplyMessage, kMatrixMultiplyService_service_id, kMatrixMultiplyService_erpcMatrixMultiply_id, sequence);
    }

    if (!err)
    {
        for (uint32_t arrayCount1 = 0; arrayCount1 < 5; ++arrayCount1)
        {
            for (uint32_t arrayCount2 = 0; arrayCount2 < 5; ++arrayCount2)
            {
                if (!err)
                {
                    err = out->write((*result_matrix)[arrayCount1][arrayCount2]);
                }
                else
                {
                    break;
                }
            }
        }
    }

    if (!err)
    {
        err = out->endWriteMessage();
    }


    if (matrix1)
    {
        erpc_free(matrix1);
    }

    if (matrix2)
    {
        erpc_free(matrix2);
    }

    if (result_matrix)
    {
        erpc_free(result_matrix);
    }
    return err;
}
erpc_service_t create_MatrixMultiplyService_service()
{
    return new (nothrow) MatrixMultiplyService_service();
}
