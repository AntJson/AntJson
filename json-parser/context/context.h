//
// Created by danysmall on 5/7/23.
//
#include <stdint.h>

#ifndef DTOCONSTRUCTOR_CONTEXT_H
#define DTOCONSTRUCTOR_CONTEXT_H

typedef struct Context_s Context;

typedef enum {
  contextObject = 0,
  contextKey    = 1,
  contextValue  = 2,
} ContextType;

typedef struct Context_s {
    ContextType contextType;
    Context* parent;
    Context* child;
    uint16_t depth;
    uint32_t openLiteralPos;
} Context;


// Initialization + Destruction
Context* contextInit();
int contextDispose(Context* context);

// Setters
int contextSetType(Context* context, ContextType type);
int contextSetDepth(Context* context, uint16_t depth);
int contextSetOpenLiteralPos(Context* context, uint32_t pos);

// Other
int contextIncreaseDepth(Context* context);
int contextAddChild(Context* parent, Context* child);

#endif //DTOCONSTRUCTOR_CONTEXT_H
