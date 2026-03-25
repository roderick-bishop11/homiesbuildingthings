#include "strings.h"

MessageCache messageCache;

bool MessageCache::isLpeModeEnabled()
{
    return pref_getCheckbox("lpe", false);
}

static const char *randomMessage(const std::vector<const char *> &messages)
{
    if (messages.empty())
        return "???";
    return messages[random(0, messages.size())];
}

static const std::vector<const char *> genericPresetMessages = {
    "Okaaay, let's go!",
    "Been on Reddit today yet?",
    "Are you hydrated?",
    "Maybe a little coffee break?",
    "It's about time to call it\na day, isn't it?",
    "Nice here, but have you been\non Reddit today?",
    "You got this (we hope)",
    "Let's see what happens\n\n                              what happens",
};

static const std::vector<const char *> chatGptFacts = {
    "An elephant's brain\ncontains over 257 billion neurons\nand shows strong emotions.",

    "Octopuses have three hearts\nand a sophisticated nervous system\nthat solves problems efficiently.",

    "Birds have magnetoreceptors\nthat help them use Earth's magnetic field\nas a compass.",

    "Bees communicate through a\nprecise waggle dance, with which they\ntransmit food sources.",

    "Snakes sense heat through\nspecialized receptors,\nmaking them skilled hunters.",

    "Lungfish breathe with gills\nand primitive lungs,\nbridging water and land.",

    "Chameleons change their color\nnot just for camouflage,\nbut also for communication.",

    "Coyotes are very adaptable\nand live in various environments,\nfrom deserts to cities.",

    "Hummingbirds are the only birds\nthat can fly backwards,\nthanks to special flight muscles.",

    "Giraffes have a complex\ncirculatory system that supplies their head\nwith oxygen-rich blood.",

    "Sharks have ampullae of Lorenzini,\nwhich help them sense weak\nelectrical fields.",

    "An ant colony can carry the weight\nof several elephants",

    "Sloths move very slowly,\nso algae can settle\nand keep them well camouflaged.",

    "Cheetahs reach top\nspeeds, but can\nonly run briefly.",

    "Starfish have no brain,\nbut a distributed nervous system\nthat works in their arms.",

    "Whales use infrasound,\nwhose tones spread over many km\nin the ocean.",

    "Axolotls regenerate limbs,\nmaking them interesting\nresearch subjects.",

    "Penguins store heat\nby keeping their feathers tight\nand minimizing heat loss.",

    "The DNA of many animals shows amazing\nsimilarities that reveal evolutionary\nrelationships.",

    "Butterflies have sophisticated\ncolor recognition systems",

    "Humans and bananas\nshare about 60% of their genes,\na hint at shared roots.",
    "Jellyfish have ancient genes\nthat have barely changed.",
    "Koalas have\nfingerprint-like ridges,\nsimilar to humans.",
    "Sharks and rays\nshare genetic roots\nand belong to the cartilaginous fish family.",

    "Every move on the board\nis a rebellion; no piece is sacred,\nand the king is just another target.",

    "In chess, chaos is art,\neach pawn a revolutionary spark,\nevery check a call to arms.",

    "Google en passant\n\n                          holy hell!",

    "When dinosaurs existed,\nthere were volcanoes erupting\non the moon.",

    "The only letters that\ndon't appear in the periodic table\nare 'J' and 'Q'.",

    "When a polar bear and a\ngrizzly bear mate,\nit's called a 'Pizzy Bear'.",

    "Daniel Radcliffe was allergic to\nhis Harry Potter glasses,\nbut Harry Potter wears them.",

    "In English it's called a 'French Exit'\nwhen you leave without saying goodbye",

    "In Arizona, cutting down a\nSaguaro cactus can be prosecuted\nas a crime.",

    "The Buddha shown in statues\nis not the real Buddha;\nthe real one was thin from asceticism.",

    "A single spaghetti strand\nis called 'spaghetto',\na curious fact.",

    "Princess Peach stayed silent\nuntil 1988, as designers\ndidn't make her moveable.",

    "The first movie with a soundtrack\nwas Snow White\nand the Seven Dwarfs.",

    "If you hold your car keys\nto your head, it increases\nthe range of the remote control.",

    "Fruit stickers are edible,\njust like the fruit itself;\nWash before eating!",

    "The giant anteater's name\nis Myrmecophaga Tridactyla,\nwhich means 'ant-eating with 3 fingers'.",

    "The word 'astronaut' comes\nfrom Greek 'astro' = star,\nand 'naut' means sailor."

};

static const std::vector<const char *>
    genericStartBreakMessages = {"Break time!", "Take a rest", "Time to relax", "Well done!"};

extern const std::vector<const char *> lpeStartBreakMessages = {};
static const std::vector<const char *> lpeEmailPresetMessages = {};
static const std::vector<const char *> lpeCodingPresetMessages = {};

static const char *generateMessage(Messages message)
{
    const char *result = "";
    std::vector<const char *> messages;
    messages.insert(messages.end(), chatGptFacts.begin(), chatGptFacts.end());
    messages.insert(messages.end(), genericPresetMessages.begin(), genericPresetMessages.end());

    bool lpeModeEnabled = messageCache.isLpeModeEnabled();

    switch (message)
    {
    case Messages::TimerWaitingForConfirmationStartOfBreak_Header:
        result = "Done!";
        break;

    case Messages::TimerWaitingForConfirmationEndOfBreak_Header:
        result = "Break over";
        break;

    case Messages::Break_PauseText:
        result = "Break";
        break;

    case Messages::Break_LongPauseText:
        result = "Long break";
        break;

    // Menu items
    case Messages::MenuItem_Pause:
        if (lpeModeEnabled)
        {
            result = "Be right back";
        }
        else
        {
            result = "Pause";
        }
        break;
    case Messages::MenuItem_Resume:
        if (lpeModeEnabled)
        {
            result = "I'm back";
        }
        else
        {
            result = "Resume";
        }
        break;
    case Messages::MenuItem_BreakNow:
        if (lpeModeEnabled)
        {
            result = "ENOUGH!";
        }
        else
        {
            result = "Break now";
        }
        break;
    case Messages::MenuItem_SkipBreak:
        if (lpeModeEnabled)
        {
            result = "Skip break";
        }
        else
        {
            result = "Skip break";
        }
        break;
    case Messages::MenuItem_Cancel:
        result = "Stop";
        break;
    case Messages::MenuItem_BackToPresets:
        result = "Back to selection";
        break;
    case Messages::MenuItem_RestartTimer:
        if (lpeModeEnabled)
        {
            result = randomMessage({"Once more!", "AGAIN!", "Here we go again...", "Do it agane"});
        }
        else
        {
            result = randomMessage({"Restart", "Let's go again", "One more time"});
        }
        break;
    case Messages::MenuItem_StartBreak:
        if (lpeModeEnabled)
        {
            result = randomMessage(lpeStartBreakMessages);
        }
        else
        {
            result = randomMessage(genericStartBreakMessages);
        }
        break;

    // Timer states
    case Messages::TimerState_Paused:
        result = "- PAUSED -";
        break;

    // Time formats
    case Messages::TimeFormat_Minutes:
        result = "min";
        break;
    case Messages::TimeFormat_Seconds:
        result = "sec";
        break;

    // Preset specific
    case Messages::Preset_Email_Message:
        if (lpeModeEnabled)
        {
            messages.insert(messages.end(), lpeEmailPresetMessages.begin(), lpeEmailPresetMessages.end());
        }
        result = randomMessage(messages);
        break;

    case Messages::Preset_Coding_Message:
        if (lpeModeEnabled)
        {
            messages.insert(messages.end(), lpeCodingPresetMessages.begin(), lpeCodingPresetMessages.end());
        }
        result = randomMessage(messages);
        break;

    case Messages::Preset_Focus_Message:
        result = randomMessage(messages);
        break;

    case Messages::Statistics:
        result = "Statistics";
        break;

    case Messages::Statistics_CurrentCycle:
        result = "Current cycle";
        break;

    case Messages::Statistics_CurrentTime:
        result = "Work time";
        break;

    case Messages::Statistics_CurrentBreakTime:
        result = "Break time";
        break;

    case Messages::Statistics_TotalCycles:
        result = "Cycles";
        break;

    case Messages::Statistics_TotalTime:
        result = "Work time";
        break;

    case Messages::Statistics_TotalBreakTime:
        result = "Break time";
        break;

    default:
        result = "???";
        break;
    }

    return result;
}

const char *MessageCache::getMessage(Messages message)
{
    auto it = cache.find(message);
    if (it != cache.end())
    {
        return it->second;
    }

    const char *result = generateMessage(message);
    cache[message] = result;
    return result;
}

void MessageCache::clearCache(Messages message)
{
    cache.erase(message);
}

void MessageCache::clearAllCache()
{
    cache.clear();
}

std::vector<const char *> MessageCache::getMessages()
{
    std::vector<const char *> messages;
    // append vectors
    messages.insert(messages.end(), genericPresetMessages.begin(), genericPresetMessages.end());
    messages.insert(messages.end(), genericStartBreakMessages.begin(), genericStartBreakMessages.end());
    messages.insert(messages.end(), lpeStartBreakMessages.begin(), lpeStartBreakMessages.end());
    messages.insert(messages.end(), lpeEmailPresetMessages.begin(), lpeEmailPresetMessages.end());
    messages.insert(messages.end(), lpeCodingPresetMessages.begin(), lpeCodingPresetMessages.end());
    messages.insert(messages.end(), chatGptFacts.begin(), chatGptFacts.end());

    return messages;
}