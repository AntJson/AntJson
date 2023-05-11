//
// Created by danysmall on 5/7/23.
//

#include <stdlib.h>
#include "context.h"
#include "../../constants/errors.h"

Context* contextInit() {
    Context* context = (Context*)malloc(sizeof(Context));
    return context;
}

int checkContextOnNull(Context* context) {
    if (context == NULL) {
        return operationOnNullContext;
    }
    return 0;
}

int contextDispose(Context* context) {
    if (context != NULL) {
        free(context);
        return 0;
    }
    return disposeWithNullPtr;
}

int contextSetType(Context* context, ContextType type) {
    int error = checkContextOnNull(context);
    if (!error) {
        context->contextType = type;
    }
    return error;
}

int contextSetDepth(Context* context, uint16_t depth) {
    int error = checkContextOnNull(context);
    if (!error) {
        context->depth = depth;
    }
    return error;
}

int contextSetOpenLiteralPos(Context* context, uint32_t pos) {
    int error = checkContextOnNull(context);
    if (!error) {
        context->openLiteralPos = pos;
    }
    return error;
}

int contextIncreaseDepth(Context* context) {
    int error = checkContextOnNull(context);
    if (!error) {
        context->depth++;
    }
    return error;
}

int contextAddChild(Context* parent, Context* child) {
    if (parent != NULL && child != NULL) {
        child->parent = parent;
        parent->child = child;
    }
}