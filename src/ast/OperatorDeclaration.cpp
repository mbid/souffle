/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2020 The Souffle Developers. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

#include "ast/OperatorDeclaration.h"
#include "souffle/utility/ContainerUtil.h"
#include "souffle/utility/DynamicCasting.h"
#include "souffle/utility/FunctionalUtil.h"
#include "souffle/utility/StreamUtil.h"
#include "souffle/utility/tinyformat.h"
#include <cassert>
#include <ostream>
#include <utility>

namespace souffle::ast {

OperatorDeclaration::OperatorDeclaration(
        std::string name, VecOwn<Attribute> params, Own<Attribute> returnType, SrcLocation loc)
        : Node(std::move(loc)), name(std::move(name)), params(std::move(params)),
          returnType(std::move(returnType)) {
    assert(this->name.length() > 0 && "operator name is empty");
    assert(allValidPtrs(this->params));
    assert(this->returnType != nullptr);
}

void OperatorDeclaration::print(std::ostream& out) const {
    auto convert = [&](Own<Attribute> const& attr) {
        return attr->getName() + ": " + attr->getTypeName().toString();
    };

    tfm::format(out, ".operator %s(%s): %s", name, join(map(params, convert), ","), returnType->getTypeName());
    out << std::endl;
}

bool OperatorDeclaration::equal(const Node& node) const {
    const auto& other = asAssert<OperatorDeclaration>(node);
    return name == other.name && params == other.params && returnType == other.returnType;
}

OperatorDeclaration* OperatorDeclaration::cloning() const {
    return new OperatorDeclaration(name, clone(params), clone(returnType), getSrcLoc());
}

}  // namespace souffle::ast
