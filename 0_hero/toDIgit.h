#pragma once
#include <string>
#include <iostream>
#include <variant>


namespace digcnv {
	using Data = std::variant<int, double>;

	struct DataPrinter {
		std::ostream& out;
		void operator()(int value) const {
			out << value;
		}
		void operator()(double value) const {
			out << value;
		}
	};

	std::ostream& operator<<(std::ostream& out, const Data& value) {
		std::visit(DataPrinter{ out }, value);
		return out;
	}

	class ParsingError : public std::runtime_error {
	public:
		using runtime_error::runtime_error;
	};

	class toDigit {
	public:
		explicit toDigit(const char* str) : base_str_(str) {
			this->convert();
		}
		~toDigit(){}

		std::string_view origin() const {
			return { this->base_str_ };
		}

		bool IsInt() const {
			return std::holds_alternative<int>(this->converted_);
		}
		bool IsDouble() const {
			return std::holds_alternative<double>(this->converted_);
		}

		int AsInt() const {
			if (this->IsInt()) {
				return std::get<int>(this->converted_);
			} else {
				throw ParsingError("No INT in " + std::string(this->origin()));
			}
		}
		double AsDouble() const {
			if (this->IsDouble()) {
				return std::get<double>(this->converted_);
			} else {
				throw ParsingError("No DOUBLE in " + std::string(this->origin()));
			}
		}

	private:
		enum class State {
			sign = 0, intpart = 1, dot = 2, denominator = 3, power = 4, powersign = 5, powerint = 6
		};

		void convert() {
			int int_part = 0;
			double den_part = 0;
			double delim = 10;
			int E = 0;

			auto ptr = this->base_str_;
			while (*ptr != '\0') {
				const char str_char = *ptr;
				switch (this->state_) {
					case(State::sign):
						if (str_char == '-') {
							this->sign_ = true;
							this->state_ = State::intpart;
						} else if (str_char == '+') {
							this->state_ = State::intpart;
						} else if (str_char >= '0' && str_char <= '9') {
							int_part *= 10;
							int_part += (str_char - 48);
							this->state_ = State::intpart;
						} else {
							throw ParsingError("Convert error - sign statement " + str_char);
						}
						break;
					case(State::intpart):
						if (str_char >= '0' && str_char <= '9') {
							int_part *= 10;
							int_part += (str_char - 48);
						} else if (str_char == '.') {
							this->state_ = State::dot;
						} else if (str_char == '\0') {
							break;
						} else {
							throw ParsingError("Convert error - intpart statement " + str_char);
						}
						break;
					case(State::dot):
						if (str_char >= '0' && str_char <= '9') {
							this->state_ = State::denominator;
							den_part += ((str_char - 48) / delim);
							delim *= 10;
						} else if (str_char == '\0') {
							break;
						} else {
							throw ParsingError("Convert error - dot statement " + str_char);
						}
						break;
					case(State::denominator):
						if (str_char >= '0' && str_char <= '9') {
							den_part += ((str_char - 48) / delim);
							delim *= 10;
						} else if (str_char == 'e') {
							this->state_ = State::power;
						} else if (str_char == '\0') {
							break;
						} else {
							throw ParsingError("Convert error - denominator statement " + str_char);
						}
						break;
					case(State::power):
						if (str_char == '-') {
							this->power_sign_ = true;
							this->state_ = State::powersign;
						} else if (str_char == '+') {
							this->state_ = State::powersign;
						} else if (str_char >= '0' && str_char <= '9') {
							this->state_ = State::powerint;
							E *= 10;
							E += (str_char - 48);
						} else {
							throw ParsingError("Convert error - power statement " + str_char);
						}
						break;
					case(State::powersign):
						if (str_char >= '0' && str_char <= '9') {
							E *= 10;
							E += (str_char - 48);
							this->state_ = State::powerint;
						} else {
							throw ParsingError("Convert error - powersign statement " + str_char);
						}
						break;
					case(State::powerint):
						if (str_char >= '0' && str_char <= '9') {
							E *= 10;
							E += (str_char - 48);
						} else if (str_char == '\0') {
							break;
						} else {
							throw ParsingError("Convert error - powerint statement " + str_char);
						}
						break;
					default:
						throw ParsingError("Convert error - main statement " + str_char);
						break;
				}
				ptr++;
			}

			if (this->state_ == State::sign) {
				throw ParsingError("Convert error - first sign statement");
			} else if (this->state_ == State::power && E == 0) {
				throw ParsingError("Convert error - power statement");
			} else if (this->state_ == State::intpart) {
				this->sign_ == true ? int_part *= -1 : int_part;
				this->converted_ = int_part;
			} else {
				double res = (double)int_part + den_part;
				this->sign_ == true ? res *= -1 : res;

				if (E > 0) {
					if (this->power_sign_) {
						while (E) {
							res /= 10;
							E--;
						}
					} else {
						while (E) {
							res *= 10;
							E--;
						}
					}
				}
				this->converted_ = res;
			}
		}

		bool sign_ = false;
		bool power_sign_ = false;
		State state_{ State::sign };
		const char* base_str_{ nullptr };
		Data converted_;
	};
} //namespace digcnv
