// Copyright 2023 Bloomberg Finance L.P.
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// bmqa_openqueuestatus.t.cpp                                         -*-C++-*-
#include <bmqa_openqueuestatus.h>

// BMQ
#include <bmqa_queueid.h>
#include <bmqimp_queue.h>
#include <bmqt_correlationid.h>
#include <bmqt_resultcode.h>
#include <bmqt_uri.h>

// MWC
#include <mwcu_memoutstream.h>

// BDE
#include <bsl_memory.h>
#include <bsl_string.h>

// TEST DRIVER
#include <mwctst_testhelper.h>

// CONVENIENCE
using namespace BloombergLP;
using namespace bsl;




// ============================================================================
//                                 MAIN PROGRAM
// ----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    TEST_PROLOG(mwctst::TestHelper::e_DEFAULT);

    bmqt::UriParser::initialize(s_allocator_p);

    switch (_testCase) {
    case 0:
    case 3: test3_print(); break;
    case 2: test2_comparison(); break;
    case 1: test1_breathingTest(); break;
    default: {
        cerr << "WARNING: CASE '" << _testCase << "' NOT FOUND." << endl;
        s_testStatus = -1;
    } break;
    }

    bmqt::UriParser::shutdown();

    TEST_EPILOG(mwctst::TestHelper::e_CHECK_DEF_GBL_ALLOC);
}
