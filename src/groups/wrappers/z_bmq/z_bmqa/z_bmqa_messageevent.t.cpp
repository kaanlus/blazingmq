// Copyright 2014-2023 Bloomberg Finance L.P.
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

// bmqa_messageevent.t.cpp                                            -*-C++-*-
#include <z_bmqa_messageevent.h>

// BMQ
#include <bmqa_messageiterator.h>
#include <bmqimp_event.h>
#include <bmqp_ackeventbuilder.h>
#include <bmqp_crc32c.h>
#include <bmqp_event.h>
#include <bmqp_messageguidgenerator.h>
#include <bmqp_protocolutil.h>
#include <bmqp_puteventbuilder.h>
#include <bmqt_messageguid.h>

// BDE
#include <bdlb_random.h>
#include <bdlbb_blobutil.h>
#include <bdlbb_pooledblobbufferfactory.h>
#include <bslma_usesbslmaallocator.h>

// TEST DRIVER
#include <mwctst_testhelper.h>

// CONVENIENCE
using namespace BloombergLP;
using namespace bsl;

// ============================================================================
//                            TEST HELPERS UTILITY
// ----------------------------------------------------------------------------
namespace {

int seed = bsl::numeric_limits<int>::max();

/// struct representing the parameters that `AckEventBuilder::appendMessage`
/// takes.
struct AckData {
    int               d_status;
    int               d_corrId;
    bmqt::MessageGUID d_guid;
    int               d_queueId;
};

/// Append the specified `numMsgs` messages to the specified `builder` and
/// populate the specified `vec` with the messages that were added, so that
/// the caller can correlate the builder's data to what was added.
static void appendMessages(bmqp::AckEventBuilder* builder,
                           bsl::vector<AckData>*  vec,
                           size_t                 numMsgs)
{
    static const char* s_HEX_REP[] = {"0000000000003039CD8101000000270F",
                                      "00000000010EA8F9515DCACE04742D2E",
                                      "ABCDEF0123456789ABCDEF0123456789"};

    const int k_NUM_GUIDS = sizeof(s_HEX_REP) / sizeof(s_HEX_REP[0]);

    vec->reserve(numMsgs);

    for (size_t i = 0; i < numMsgs; ++i) {
        AckData data;
        data.d_status = i % 3;
        data.d_corrId = i * i;
        data.d_guid.fromHex(s_HEX_REP[i % k_NUM_GUIDS]);
        data.d_queueId = i;
        int rc         = builder->appendMessage(data.d_status,
                                        data.d_corrId,
                                        data.d_guid,
                                        data.d_queueId);
        ASSERT_EQ(rc, 0);
        vec->push_back(data);
    }
}

struct PutData {
    BSLMF_NESTED_TRAIT_DECLARATION(PutData, bslma::UsesBslmaAllocator)

    PutData(bslma::Allocator* allocator)
    : d_qid()
    , d_guid()
    , d_payload(allocator)
    {
    }

    PutData(const PutData& rhs, bslma::Allocator* allocator)
    : d_qid(rhs.d_qid)
    , d_guid(rhs.d_guid)
    , d_payload(rhs.d_payload, allocator)
    {
    }

    int               d_qid;
    bmqt::MessageGUID d_guid;
    bdlbb::Blob       d_payload;
};

bmqt::EventBuilderResult::Enum
appendMessage(size_t                    iteration,
              bmqp::PutEventBuilder*    peb,
              bsl::vector<PutData>*     vec,
              bdlbb::BlobBufferFactory* bufferFactory,
              bslma::Allocator*         allocator)
{
    PutData data(allocator);

    data.d_guid = bmqp::MessageGUIDGenerator::testGUID();
    data.d_qid  = iteration;

    bdlbb::Blob payload(bufferFactory, allocator);
    int         blobSize = bdlb::Random::generate15(&seed);
    bsl::string str(blobSize, 'x', allocator);
    bdlbb::BlobUtil::append(&payload, str.c_str(), blobSize);

    data.d_payload = payload;

    vec->push_back(data);

    if (0 == iteration || 0 == blobSize % 2) {
        peb->startMessage();
    }

    peb->setMessagePayload(&data.d_payload);
    peb->setMessageGUID(data.d_guid);
    return peb->packMessage(data.d_qid);
}

}  // close unnamed namespace


// ============================================================================
//                                    TESTS
// ----------------------------------------------------------------------------

static void test1_breathingTest()
{
    mwctst::TestHelper::printTestName("BREATHING TEST");

    MessageEvent ** obj;
    z_bmqa_MessageEvent__create(&obj);

    z_bmqa_MessageEvent__delete(&obj);

}



// ============================================================================
//                                 MAIN PROGRAM
// ----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    TEST_PROLOG(mwctst::TestHelper::e_DEFAULT);

    // Temporary workaround to suppress the 'unused operator
    // NestedTraitDeclaration' warning/error generated by clang.  TBD: figure
    // out the right way to "fix" this.
    PutData dummy(s_allocator_p);
    static_cast<void>(
        static_cast<bslmf::NestedTraitDeclaration<PutData,
                                                  bslma::UsesBslmaAllocator> >(
            dummy));

    bmqp::ProtocolUtil::initialize(s_allocator_p);

    switch (_testCase) {
    case 0:
    case 3: test3_putMessageIteratorTest(); break;
    case 2: test2_ackMesageIteratorTest(); break;
    case 1: test1_breathingTest(); break;
    default: {
        cerr << "WARNING: CASE '" << _testCase << "' NOT FOUND." << endl;
        s_testStatus = -1;
    } break;
    }

    bmqp::ProtocolUtil::shutdown();

    TEST_EPILOG(mwctst::TestHelper::e_CHECK_DEF_GBL_ALLOC);
}
