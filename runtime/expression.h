#ifndef __expression_h__
#define __expression_h__

#include <vector>

using namespace std;

namespace fuzuli {
    namespace expression {

        enum _ExpressionType {
            IdentifierExpression,
            StringConstantExpression
        };

        typedef enum _ExpressionType ExpressionType;

        struct _Expression {
            ExpressionType type;
            vector<_Expression*> expressions;
            union  {
                int i;
                double d;
                void *ptr;
                const char *cc;
                float f;
                long l;
            } constant;
        };

        typedef struct _Expression Expression;


    } // end of namespace expression
} // end of namespace fuzuli

#endif

