/*
   Unix SMB/CIFS implementation.
   test suite for negoex ndr operations

   Copyright (C) Guenther Deschner 2015

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "includes.h"
#include "torture/ndr/ndr.h"
#include "librpc/gen_ndr/ndr_negoex.h"
#include "torture/ndr/proto.h"

static const uint8_t negoex_MESSAGE_ARRAY_data[] = {
	0x4e, 0x45, 0x47, 0x4f, 0x45, 0x58, 0x54, 0x53, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00,
	0x06, 0xcb, 0x30, 0x71, 0x62, 0x20, 0x1b, 0x6a, 0x40, 0x9e, 0x35, 0x14,
	0xc2, 0x6b, 0x17, 0x73, 0xba, 0x25, 0xdd, 0x80, 0x91, 0xfb, 0xae, 0x2c,
	0x68, 0x4b, 0x99, 0x28, 0xf0, 0x3c, 0x3e, 0xf3, 0xe2, 0xcf, 0x60, 0xa3,
	0x29, 0xee, 0xa0, 0xf9, 0xb1, 0x10, 0x4b, 0x56, 0xc3, 0x83, 0xc7, 0x32,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x5c, 0x33, 0x53, 0x0d, 0xea, 0xf9, 0x0d, 0x4d, 0xb2, 0xec, 0x4a, 0xe3,
	0x78, 0x6e, 0xc3, 0x08, 0x4e, 0x45, 0x47, 0x4f, 0x45, 0x58, 0x54, 0x53,
	0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
	0x98, 0x00, 0x00, 0x00, 0x06, 0xcb, 0x30, 0x71, 0x62, 0x20, 0x1b, 0x6a,
	0x40, 0x9e, 0x35, 0x14, 0xc2, 0x6b, 0x17, 0x73, 0x5c, 0x33, 0x53, 0x0d,
	0xea, 0xf9, 0x0d, 0x4d, 0xb2, 0xec, 0x4a, 0xe3, 0x78, 0x6e, 0xc3, 0x08,
	0x40, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x30, 0x56, 0xa0, 0x54,
	0x30, 0x52, 0x30, 0x27, 0x80, 0x25, 0x30, 0x23, 0x31, 0x21, 0x30, 0x1f,
	0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x18, 0x54, 0x6f, 0x6b, 0x65, 0x6e,
	0x20, 0x53, 0x69, 0x67, 0x6e, 0x69, 0x6e, 0x67, 0x20, 0x50, 0x75, 0x62,
	0x6c, 0x69, 0x63, 0x20, 0x4b, 0x65, 0x79, 0x30, 0x27, 0x80, 0x25, 0x30,
	0x23, 0x31, 0x21, 0x30, 0x1f, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x18,
	0x54, 0x6f, 0x6b, 0x65, 0x6e, 0x20, 0x53, 0x69, 0x67, 0x6e, 0x69, 0x6e,
	0x67, 0x20, 0x50, 0x75, 0x62, 0x6c, 0x69, 0x63, 0x20, 0x4b, 0x65, 0x79
};

static bool negoex_MESSAGE_ARRAY_check(struct torture_context *tctx,
				       struct negoex_MESSAGE_ARRAY *r)
{
	struct GUID guid;
	struct negoex_MESSAGE m;

	torture_assert_int_equal(tctx, r->count, 2, "count");

	m = r->messages[0];

	torture_assert_str_equal(tctx, m.signature, "NEGOEXTS", "signature");
	torture_assert_int_equal(tctx, m.type, NEGOEX_MESSAGE_TYPE_ACCEPTOR_NEGO, "type");
	torture_assert_int_equal(tctx, m.sequence_number, 0, "sequence_number");
	torture_assert_int_equal(tctx, m.header_length, 96, "header_length");
	torture_assert_int_equal(tctx, m.message_length, 112, "message_length");
	GUID_from_string("7130cb06-2062-6a1b-409e-3514c26b1773", &guid);
	torture_assert_guid_equal(tctx, m.conversation_id, guid, "conversation_id");
	/* torture_assert_int_equal(tctx, m.p.nego.random, ba25dd8091fbae2c684b9928f03c3ef3e2cf60a329eea0f9b1104b56c383c732, "p.nego.random"); */
	torture_assert_int_equal(tctx, m.p.nego.protocol_version, 0, "p.nego.protocol_version");
	torture_assert_int_equal(tctx, m.p.nego.auth_schemes.count, 1, "p.nego.auth_schemes.count");
	GUID_from_string("0d53335c-f9ea-4d0d-b2ec-4ae3786ec308", &guid);
	torture_assert_guid_equal(tctx, m.p.nego.auth_schemes.array[0].guid, guid, "p.nego.auth_schemes.array[0].guid");
	torture_assert_int_equal(tctx, m.p.nego.extensions.count, 0, "p.nego.extensions.count");

	m = r->messages[1];

	torture_assert_str_equal(tctx, m.signature, "NEGOEXTS", "signature");
	torture_assert_int_equal(tctx, m.type, NEGOEX_MESSAGE_TYPE_ACCEPTOR_META_DATA, "type");
	torture_assert_int_equal(tctx, m.sequence_number, 1, "sequence_number");
	torture_assert_int_equal(tctx, m.header_length, 64, "header_length");
	torture_assert_int_equal(tctx, m.message_length, 152, "message_length");
	GUID_from_string("7130cb06-2062-6a1b-409e-3514c26b1773", &guid);
	torture_assert_guid_equal(tctx, m.conversation_id, guid, "conversation_id");
	GUID_from_string("0d53335c-f9ea-4d0d-b2ec-4ae3786ec308", &guid);
	torture_assert_guid_equal(tctx, m.p.exchange.auth_scheme.guid, guid, "auth_scheme.guid");
	torture_assert_int_equal(tctx, m.p.exchange.exchange.blob.length, 88, "exchange.blob.length");

	return true;
}

struct torture_suite *ndr_negoex_suite(TALLOC_CTX *ctx)
{
	struct torture_suite *suite = torture_suite_create(ctx, "negoex");

	torture_suite_add_ndr_pull_validate_test(suite, negoex_MESSAGE_ARRAY,
					    negoex_MESSAGE_ARRAY_data,
					    negoex_MESSAGE_ARRAY_check);

	return suite;
}
