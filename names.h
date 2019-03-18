#ifndef LHAT_NAMES_H
#define LHAT_NAMES_H

#include <string>
#include <unordered_map>
#include <vector>

namespace lhat {
// NameContext is a context of names of lambda variables.
class NameContext {
public:
  // AddName adds name to the context and returns its index. If name is already
  // present in the context its index is returned.
  int AddName(const std::string& name);

  // GetNameForIndex returns the name that corresponds to index idx.
  std::string GetNameForIndex(int idx) const;

  // GetIndexForName returns the index that corresponds to name.
  int GetIndexForName(const std::string& name) const;

private:
  std::vector<std::string> names_;
  std::unordered_map<std::string, int> name_to_idx_;
};
}  // namespace lhat

#endif  // LHAT_NAMES_H
