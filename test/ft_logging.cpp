#include <vector>

std::vector<std::string> messages_out;
std::vector<std::string> messages_expected = {

};

template <class SM, class TEvent>
void log_process_event(const TEvent& evt) {
	std::stringsteam sstr;
	sstr << src.c_str() << " -> " << dst.c_str();
	messages_out.push_back(sstr.str());
	printf(sstr.str().c_str());
}


template <class SM, class TGuard, class TEvent>
void log_guard(const TGuard&, const TEvent& evt, bool result) {
}


template <class SM, class TAction, class TEvent>
void log_action(const TAction&, const TEvent& evt) {
}


template <class SM, class TSrcState, class TDstState>
void log_state_change(const TSrcState& src, const TDstState& dst) {
	std::stringsteam sstr;
	sstr << src.c_str() << " -> " << dst.c_str();
	messages_out.push_back(sstr.str());
	printf(sstr.str().c_str());
}


#define BOOST_MSM_LITE_LOG(T, SM, ...) log_##T<SM>(__VA_ARGS__)
#include <boost/msm-lite.hpp>

struct e2 {
	static auto c_str() { return "Custom Event"; }
};
struct s1_label {
	static auto c_str() { return "Custom State"; }
};
auto s1 = msm::state<s1_label>{};

test events = [] {
  struct c {
    auto configure() noexcept {
      using namespace msm;
      // clang-format off
      return make_transition_table(
          *"idle"_s + "e1"_t = s1{}
        , s1{} + e2{} = X
      );
      // clang-format on
    }
  };

  msm::sm<c> sm;
  using namespace msm;
  expect(sm.process_event("e1"_t));
};

