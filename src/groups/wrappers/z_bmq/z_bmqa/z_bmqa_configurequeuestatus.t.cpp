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

// bmqa_configurequeuestatus.t.cpp                                    -*-C++-*-
#include <z_bmqa_configurequeuestatus.h>

// BMQ
#include <bmqa_queueid.h>
#include <bmqimp_queue.h>
#include <bmqt_correlationid.h>
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
//                                    TESTS
// ----------------------------------------------------------------------------

static void test1_breathingTest()
// ------------------------------------------------------------------------
// BREATHING TEST
//
// Concerns:
//   Exercise basic functionality before beginning testing in earnest.
//   Probe that functionality to discover basic errors.
//
// Testing:
//   Basic functionality.
// ------------------------------------------------------------------------
{
    mwctst::TestHelper::printTestName("BREATHING TEST");

    PV("Default Constructor");
    {
        ConfigureQueueStatus ** obj;
        z_bmqa_ConfigureQueueStatus__create(&obj);
        ASSERT_EQ(bool(obj), true);
        ASSERT_EQ(obj.result(), bmqt::ConfigureQueueResult::e_SUCCESS);
        ASSERT_EQ(obj.errorDescription(), bsl::string("", s_allocator_p));

        z_bmqa_ConfigureQueueStatus__delete(&obj);
    }

    PV("Valued Constructor");
    {
        const bmqt::CorrelationId correlationId =
            bmqt::CorrelationId::autoValue();
        const bmqa::QueueId queueId = bmqa::QueueId(correlationId,
                                                    s_allocator_p);
        const bmqt::ConfigureQueueResult::Enum result =
            bmqt::ConfigureQueueResult::e_UNKNOWN;
        const bsl::string errorDescription = bsl::string("ERROR",
                                                         s_allocator_p);

        bmqa::ConfigureQueueStatus obj(queueId,
                                       result,
                                       errorDescription,
                                       s_allocator_p);

        ASSERT_EQ(bool(obj), false);
        ASSERT_EQ(obj.queueId(), queueId);
        ASSERT_EQ(obj.result(), result);
        ASSERT_EQ(obj.errorDescription(), errorDescription);
    }

    PV("Copy Constructor");
    {
        const bmqt::CorrelationId correlationId =
            bmqt::CorrelationId::autoValue();
        const bmqa::QueueId queueId = bmqa::QueueId(correlationId,
                                                    s_allocator_p);
        const bmqt::ConfigureQueueResult::Enum result =
            bmqt::ConfigureQueueResult::e_TIMEOUT;
        const bsl::string errorDescription = bsl::string("ERROR",
                                                         s_allocator_p);

        bmqa::ConfigureQueueStatus obj1(queueId,
                                        result,
                                        errorDescription,
                                        s_allocator_p);
        bmqa::ConfigureQueueStatus obj2(obj1, s_allocator_p);

        ASSERT_EQ(bool(obj1), bool(obj2));
        ASSERT_EQ(obj1.queueId(), obj2.queueId());
        ASSERT_EQ(obj1.result(), obj2.result());
        ASSERT_EQ(obj1.errorDescription(), obj2.errorDescription());
    }


}
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
