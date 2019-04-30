#pragma once

#include "rx.hh"

#include "core/foundations/ReactiveValueContext.hh"

#include "util/SimpleSubject.hh"

namespace rx::space::core{

    using ReactiveMemberValueStream = rx::observable<core::ReactiveValueContextPtr>;

    using ReactiveMemberValueSimpleSubject = util::SimpleSubject<core::ReactiveValueContextPtr>;
}