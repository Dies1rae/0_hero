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
			sign = 0, intpart = 1, dot = 2, denominator = 3, power = 4, powerint = 5
		};

		void convert() {
			int int_part = 0;
			double den_part = 0;
			double delim = 10;
			int E = 0;

			
			for (auto ptr = this->base_str_; *ptr != '\0'; ptr++) {
				const char str_char = *ptr;
				if (str_char == '-' && this->state_ == State::sign) {
					this->sign_ = true;
				} else if (str_char == '+' && this->state_ == State::sign) {
					continue;
				} else if (str_char >= '0' && str_char <= '9' && this->state_ <= State::intpart) {
					this->state_ = State::intpart;
					int_part *= 10;
					int_part += (str_char - 48);
				} else if (str_char == '.' && this->state_ <= State::intpart) {
					this->state_ = State::dot;
				} else if (str_char >= '0' && str_char <= '9' && this->state_ >= State::dot && this->state_ <= State::denominator) {
					this->state_ = State::denominator;
					den_part += ((str_char - 48) / delim);
					delim *= 10;
				} else if (str_char == 'e' && (this->state_ == State::denominator || this->state_ == State::intpart)) {
					this->state_ = State::power;
					if (*(ptr + 1) == '-') {
						this->power_sign_ = true;
						ptr++;
					} else if (*(ptr + 1) == '+') {
						ptr++;
					} else {
						throw ParsingError("Convert error - E statement");
					}
				} else if (str_char >= '0' && str_char <= '9' && this->state_ >= State::power) {
					this->state_ = State::powerint;
					E *= 10;
					E += (str_char - 48);
				} else {
					throw ParsingError("Convert error - main statement " + str_char);
				}
			}

			if (this->state_ == State::sign || this->state_ == State::dot) {
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
