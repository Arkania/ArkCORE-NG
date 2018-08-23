# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  Maelstrom/TheStoneCore/boss_corborus.cpp
  Maelstrom/TheStoneCore/boss_slabhide.cpp
  Maelstrom/TheStoneCore/boss_ozruk.cpp
  Maelstrom/TheStoneCore/boss_high_priestess_azil.cpp
  Maelstrom/TheStoneCore/stonecore.h
  Maelstrom/TheStoneCore/stonecore.cpp
  Maelstrom/TheStoneCore/instance_stonecore.cpp
  Maelstrom/zone_kezan.cpp
  Maelstrom/zone_darkmoon_island.cpp
  Maelstrom/zone_deepholm.cpp
  Maelstrom/zone_lost_isles.cpp
  Maelstrom/zone_the_maelstrom.cpp
  Maelstrom/zone_tol_barad.cpp
  Maelstrom/zone_tolbarad_peninsula.cpp
)

message("  -> Prepared: The Maelstrom")
