#include "Block.h"

#include <ll/api/memory/Hook.h>
#include <mc/legacy/ActorUniqueID.h>
#include <mc/world/level/block/Block.h>
#include <mc/deps/nbt/CompoundTag.h> // <--- 这里是修改后的新路径
#include <mc/world/level/block/BlockLegacy.h>

#include "mod/Events/BlockEventHandle.h"

namespace stats {
namespace hook {
namespace {

LL_TYPE_INSTANCE_HOOK(
    BlockLegacyOnPlace,
    ll::memory::HookPriority::Normal,
    BlockLegacy,
    &BlockLegacy::onPlace,
    void,
    Block const& block,
    BlockSource& region,
    BlockPos const& pos
) {
    origin(block, region, pos);
    event::block::onPlaced(block, region, pos);
}

LL_TYPE_INSTANCE_HOOK(
    BlockLegacyPlayerDestroy,
    ll::memory::HookPriority::Normal,
    BlockLegacy,
    &BlockLegacy::playerDestroy,
    void,
    Player& player,
    BlockPos const& pos,
    Block const& block
) {
    origin(player, pos, block);
    event::block::onDestroyed(player, pos, block);
}

LL_TYPE_INSTANCE_HOOK(
    BlockLegacyOnStepOn,
    ll::memory::HookPriority::Normal,
    BlockLegacy,
    &BlockLegacy::stepOn,
    void,
    Actor& actor,
    BlockPos const& pos
) {
    origin(actor, pos);
    event::block::onStepOn(actor, pos);
}

} // namespace
} // namespace hook
} // namespace stats
