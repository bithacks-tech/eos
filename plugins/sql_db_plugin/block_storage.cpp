#include "block_storage.h"

namespace myeosio {

void block_storage::consume(const std::vector<chain::block_state_ptr> &blocks)
{
    for (const auto& block : blocks)
        ilog(block->id.str());
}

}
