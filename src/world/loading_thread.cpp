#include "loading_thread.h"

#include "world/world.h"

WorldLoadingThread::WorldLoadingThread(World &inWorld)
: world(inWorld) {}

void WorldLoadingThread::execute() {
}
