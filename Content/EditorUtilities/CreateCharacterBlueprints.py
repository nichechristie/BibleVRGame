# CreateCharacterBlueprints.py
# Run this in Unreal Engine's Python console to auto-generate all character Blueprints
# Go to Window > Developer Tools > Output Log, then run: py "Content/EditorUtilities/CreateCharacterBlueprints.py"

import unreal

# Asset tools and factory
asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
blueprint_factory = unreal.BlueprintFactory()

def create_blueprint(class_name, parent_class_path, blueprint_path, blueprint_name):
    """Create a Blueprint from a C++ class"""

    # Load the parent class
    parent_class = unreal.load_class(None, parent_class_path)
    if not parent_class:
        unreal.log_error(f"Could not load class: {parent_class_path}")
        return None

    # Set factory properties
    blueprint_factory.set_editor_property("parent_class", parent_class)

    # Create the blueprint
    blueprint = asset_tools.create_asset(
        blueprint_name,
        blueprint_path,
        unreal.Blueprint,
        blueprint_factory
    )

    if blueprint:
        unreal.log(f"Created Blueprint: {blueprint_path}/{blueprint_name}")
        # Save the asset
        unreal.EditorAssetLibrary.save_asset(f"{blueprint_path}/{blueprint_name}")
    else:
        unreal.log_error(f"Failed to create Blueprint: {blueprint_name}")

    return blueprint

# ============================================
# CREATE ALL CHARACTER BLUEPRINTS
# ============================================

# Companions
companions = [
    ("BP_Peter", "/Script/BibleVRGame.PeterCompanion"),
    ("BP_MaryMagdalene", "/Script/BibleVRGame.MaryMagdaleneCompanion"),
    ("BP_John", "/Script/BibleVRGame.JohnCompanion"),
    ("BP_Paul", "/Script/BibleVRGame.PaulCompanion"),
    ("BP_Solomon", "/Script/BibleVRGame.SolomonCompanion"),
    ("BP_TheGuide", "/Script/BibleVRGame.TheGuideCompanion"),
]

for bp_name, class_path in companions:
    create_blueprint(class_path.split(".")[-1], class_path, "/Game/Blueprints/Characters/Companions", bp_name)

# Apostles
apostles = [
    ("BP_Peter_Apostle", "/Script/BibleVRGame.PeterApostle"),
    ("BP_Andrew", "/Script/BibleVRGame.AndrewApostle"),
    ("BP_JamesGreater", "/Script/BibleVRGame.JamesGreaterApostle"),
    ("BP_John_Apostle", "/Script/BibleVRGame.JohnApostle"),
    ("BP_Philip", "/Script/BibleVRGame.PhilipApostle"),
    ("BP_Bartholomew", "/Script/BibleVRGame.BartholomewApostle"),
    ("BP_Matthew", "/Script/BibleVRGame.MatthewApostle"),
    ("BP_Thomas", "/Script/BibleVRGame.ThomasApostle"),
    ("BP_JamesLesser", "/Script/BibleVRGame.JamesLesserApostle"),
    ("BP_Thaddaeus", "/Script/BibleVRGame.ThaddaeusApostle"),
    ("BP_SimonZealot", "/Script/BibleVRGame.SimonZealotApostle"),
    ("BP_Judas", "/Script/BibleVRGame.JudasApostle"),
]

for bp_name, class_path in apostles:
    create_blueprint(class_path.split(".")[-1], class_path, "/Game/Blueprints/Characters/Apostles", bp_name)

# NPCs
npcs = [
    ("BP_Centurion", "/Script/BibleVRGame.CenturionCharacter"),
    ("BP_PontiusPilate", "/Script/BibleVRGame.PontiusPilateCharacter"),
    ("BP_Caiaphas", "/Script/BibleVRGame.CaiaphasCharacter"),
    ("BP_Nicodemus", "/Script/BibleVRGame.NicodemusCharacter"),
    ("BP_Pharisee", "/Script/BibleVRGame.PhariseeCharacter"),
    ("BP_Gabriel", "/Script/BibleVRGame.GabrielCharacter"),
    ("BP_Michael", "/Script/BibleVRGame.MichaelCharacter"),
    ("BP_MaryMother", "/Script/BibleVRGame.MaryMotherCharacter"),
    ("BP_Martha", "/Script/BibleVRGame.MarthaCharacter"),
    ("BP_MaryBethany", "/Script/BibleVRGame.MaryBethanyCharacter"),
    ("BP_WomanAtWell", "/Script/BibleVRGame.WomanAtWellCharacter"),
    ("BP_RomanSoldier", "/Script/BibleVRGame.RomanSoldier"),
    ("BP_Civilian", "/Script/BibleVRGame.CivilianCharacter"),
    ("BP_CrowdMember", "/Script/BibleVRGame.CrowdMember"),
]

for bp_name, class_path in npcs:
    create_blueprint(class_path.split(".")[-1], class_path, "/Game/Blueprints/Characters/NPCs", bp_name)

# Jesus
create_blueprint("JesusCharacter", "/Script/BibleVRGame.JesusCharacter", "/Game/Blueprints/Characters", "BP_Jesus")

# Enemy
create_blueprint("DevilCharacter", "/Script/BibleVRGame.DevilCharacter", "/Game/Blueprints/Characters/Enemy", "BP_Devil")
create_blueprint("TemptationManager", "/Script/BibleVRGame.TemptationManager", "/Game/Blueprints/Characters/Enemy", "BP_TemptationManager")

unreal.log("=== All Character Blueprints Created Successfully ===")
