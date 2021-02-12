//
// Created on February 11th 2021 by loanselot1.
//

#include "variant/VariantList.h"
#include "variant/VariantDB.h"

void OnUpdate(VariantList *v) {
    
}

int main() {
    VariantDB db;

    db.GetFunction("OnUpdate")->Bind(OnUpdate);

    VariantList v;
    v[0] = 1i8;

    db.GetFunction("OnUpdate")->fun(&v);
}  