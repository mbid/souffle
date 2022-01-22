/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2018 The Souffle Developers. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file OperatorDeclaration.h
 *
 * Defines the external functor class
 *
 ***********************************************************************/

#pragma once

#include "ast/Attribute.h"
#include "ast/Node.h"
#include "parser/SrcLocation.h"
#include "souffle/utility/Types.h"
#include <cstddef>
#include <iosfwd>
#include <string>

namespace souffle::ast {

/**
 * @class OperatorDeclaration
 * @brief Operator declaration
 *
 * Example:
 *    .operator foo(x:number, y:QuotientType):QuotientType
 */

class OperatorDeclaration : public Node {
public:
    OperatorDeclaration(std::string name, VecOwn<Attribute> params, Own<Attribute> returnType,
            SrcLocation loc = {});

    /** Return name */
    const std::string& getName() const {
        return name;
    }

    /** Return type */
    const VecOwn<Attribute>& getParams() const {
        return params;
    }

    /** Get return type */
    Attribute const& getReturnType() const {
        return *returnType;
    }

    /** Return number of arguments */
    std::size_t getArity() const {
        return params.size();
    }

protected:
    void print(std::ostream& out) const override;

private:
    bool equal(const Node& node) const override;

    OperatorDeclaration* cloning() const override;

private:
    /** Name of functor */
    const std::string name;

    /** Types of arguments */
    const VecOwn<Attribute> params;

    /** Type of the return value */
    const Own<Attribute> returnType;
};

}  // namespace souffle::ast
