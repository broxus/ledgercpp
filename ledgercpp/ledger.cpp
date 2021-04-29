#include "ledgercpp/error.hpp"
#include "ledgercpp/ledger.hpp"
#include "ledgercpp/utils.hpp"

namespace ledger {
	Ledger::Ledger() : transport_(std::make_unique<Transport>(Transport::TransportType::HID)) {

	}

	Ledger::~Ledger() {
		transport_->close();
	}

	Error Ledger::open() {
		return transport_->open();
	}

	std::tuple<ledger::Error, std::vector<uint8_t>> Ledger::get_public_key(uint32_t account, bool confirm) {
		auto payload = utils::int_to_bytes(account, 4);
		auto [err, buffer] = transport_->exchange(APDU::CLA, APDU::INS_GET_PUBLIC_KEY, confirm, 0x00, payload);
		if (err != Error::SUCCESS)
			return {err, {}};
		return {err, std::vector<uint8_t>(buffer.begin() + 1, buffer.end())};
	}

	std::tuple<Error, std::vector<uint8_t>> Ledger::sign(uint32_t account, const std::vector<uint8_t>& msg) {
		auto payload = utils::int_to_bytes(account, 4);
		payload.insert(payload.end(), msg.begin(), msg.end());
		auto [err, buffer] = transport_->exchange(APDU::CLA, APDU::INS_SIGN, 0x00, 0x00, payload);
		if (err != Error::SUCCESS)
			return {err, {}};
		return {err, std::vector<uint8_t>(buffer.begin() + 1, buffer.end())};
	}

	void Ledger::close() {
		return transport_->close();
	}
}
