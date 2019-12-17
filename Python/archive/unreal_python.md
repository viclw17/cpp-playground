StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'

LogPython: for x in range(10):
    print x

LogPython: chair_asset = unreal.load_asset('/Game/StarterContent/Props/SM_Chair.SM_Chair')
LogPython: unreal.log(chair_asset)
LogPython: <Object '/Game/StarterContent/Props/SM_Chair.SM_Chair' (0x00000211DC936000) Class 'StaticMesh'>
https://docs.unrealengine.com/en-US/PythonAPI/class/StaticMesh.html?highlight=staticmesh


LogPython: for attribute in dir(chair_asset):
    print attribute
LogPython: __class__
LogPython: __delattr__
LogPython: __doc__
LogPython: __format__
LogPython: __getattribute__
LogPython: __hash__
LogPython: __init__
LogPython: __new__
LogPython: __reduce__
LogPython: __reduce_ex__
LogPython: __repr__
LogPython: __setattr__
LogPython: __sizeof__
LogPython: __str__
LogPython: __subclasshook__
LogPython: _post_init
LogPython: _wrapper_meta_data
LogPython: add_socket
LogPython: cast
LogPython: find_socket
LogPython: get_bounding_box
LogPython: get_bounds
LogPython: get_class
LogPython: get_default_object
LogPython: get_editor_property
LogPython: get_fname
LogPython: get_full_name
LogPython: get_material
LogPython: get_material_index
LogPython: get_name
LogPython: get_num_lods
LogPython: get_num_sections
LogPython: get_outer
LogPython: get_outermost
LogPython: get_path_name
LogPython: get_typed_outer
LogPython: get_world
LogPython: global_force_mip_levels_to_be_resident
LogPython: lod_for_collision
LogPython: lpv_bias_multiplier
LogPython: modify
LogPython: never_stream
LogPython: num_cinematic_mip_levels
LogPython: remove_socket
LogPython: rename
LogPython: set_editor_property
LogPython: set_material
LogPython: static_class

LogPython: print help(chair_asset)
LogPython: Help on StaticMesh object:
class StaticMesh(StreamableRenderAsset)
 |  A StaticMesh is a piece of geometry that consists of a static set of polygons.
 |  Static Meshes can be translated, rotated, and scaled, but they cannot have their vertices animated in any way. As such, they are more efficient
 |  to render than other types of geometry such as USkeletalMesh, and they are often the basic building block of levels created in the engine.
 |  https://docs.unrealengine.com/latest/INT/Engine/Content/Types/StaticMeshes/:
 |  AStaticMeshActor, UStaticMeshComponent:
 |
 |  **C++ Source:**
 |
 |  - **Module**: Engine
 |  - **File**: StaticMesh.h
 |
 |  **Editor Properties:** (see get_editor_property/set_editor_property)
 |
 |  - ``allow_cpu_access`` (bool): [Read-Write] If true, will keep geometry data CPU-accessible in cooked builds, rather than uploading to GPU memory and releasing it from CPU memory.
 |    This is required if you wish to access StaticMesh geometry data on the CPU at runtime in cooked builds (e.g. to convert StaticMesh to ProceduralMeshComponent)
 |  - ``asset_import_data`` (AssetImportData): [Read-Write] Importing data and options used for this mesh
 |  - ``asset_user_data`` (Array(AssetUserData)): [Read-Write] Array of user data stored with the asset
 |  - ``body_setup`` (BodySetup): [Read-Write] Physics data.
 |  - ``complex_collision_mesh`` (StaticMesh): [Read-Write] Complex Collision Mesh
 |  - ``customized_collision`` (bool): [Read-Write] If the user has modified collision in any way or has custom collision imported. Used for determining if to auto generate collision on import
 |  - ``distance_field_self_shadow_bias`` (float): [Read-Write] Useful for reducing self shadowing from distance field methods when using world position offset to animate the mesh's vertices.
 |  - ``editable_mesh`` (Object): [Read-Only] The editable mesh representation of this static mesh //
 |    Maybe we don't want this visible in the details panel in the end; for now, this might aid debugging.:
 |  - ``generate_mesh_distance_field`` (bool): [Read-Write] Whether to generate a distance field for this mesh, which can be used by DistanceField Indirect Shadows.
 |    This is ignored if the project's 'Generate Mesh Distance Fields' setting is enabled.
 |  - ``global_force_mip_levels_to_be_resident`` (bool): [Read-Write] Global and serialized version of ForceMiplevelsToBeResident.
 |  - ``has_navigation_data`` (bool): [Read-Write] If true, mesh will have NavCollision property with additional data for navmesh generation and usage.
 |              Set to false for distant meshes (always outside navigation bounds) to save memory on collision data.
 |  - ``light_map_coordinate_index`` (int32): [Read-Write] The light map coordinate index
 |  - ``light_map_resolution`` (int32): [Read-Write] The light map resolution
 |  - ``lod_for_collision`` (int32): [Read-Write] Specifies which mesh LOD to use for complex (per-poly) collision.
 |    Sometimes it can be desirable to use a lower poly representation for collision to reduce memory usage, improve performance and behaviour.
 |    Collision representation does not change based on distance to camera.
 |  - ``lod_for_occluder_mesh`` (int32): [Read-Write] Specifies which mesh LOD to use as occluder geometry for software occlusion
 |    Set to -1 to not use this mesh as occluder
 |  - ``lod_group`` (Name): [Read-Write] The LOD group to which this mesh belongs.
 |  - ``lpv_bias_multiplier`` (float): [Read-Write] Bias multiplier for Light Propagation Volume lighting
 |  - ``nav_collision`` (NavCollisionBase): [Read-Only] Pre-build navigation collision
 |  - ``negative_bounds_extension`` (Vector): [Read-Write] Bound extension values in the negative direction of XYZ, positive value increases bound size
 |  - ``never_stream`` (bool): [Read-Write] Never Stream
 |  - ``num_cinematic_mip_levels`` (int32): [Read-Write] Number of mip-levels to use for cinematic quality.
 |  - ``positive_bounds_extension`` (Vector): [Read-Write] Bound extension values in the positive direction of XYZ, positive value increases bound size
 |  - ``support_gpu_uniformly_distributed_sampling`` (bool): [Read-Write] If true, a GPU buffer containing required data for uniform mesh surface sampling will be created at load time.
 |    It is created from the cpu data so bSupportUniformlyDistributedSampling is also required to be true.
 |  - ``support_uniformly_distributed_sampling`` (bool): [Read-Write] Mesh supports uniformly distributed sampling in constant time.
 |    Memory cost is 8 bytes per triangle.
 |    Example usage is uniform spawning of particles.
 |  - ``thumbnail_info`` (ThumbnailInfo): [Read-Only] Information for thumbnail rendering
 |
 |  Method resolution order:
 |      StaticMesh
 |      StreamableRenderAsset
 |      Object
 |      _ObjectBase
 |      _WrapperBase
 |      object
 |
 |  Methods defined here:
 |
 |  add_socket(...)
 |      x.add_socket(socket) -> None
 |      Add a socket object in this StaticMesh.
 |
 |      Args:
 |          socket (StaticMeshSocket):
 |
 |  find_socket(...)
 |      x.find_socket(socket_name) -> StaticMeshSocket
 |      Find a socket object in this StaticMesh by name.
 |      Entering NAME_None will return NULL. If there are multiple sockets with the same name, will return the first one.
 |
 |      Args:
 |          socket_name (Name):
 |
 |      Returns:
 |          StaticMeshSocket:
 |
 |  get_bounding_box(...)
 |      x.get_bounding_box() -> Box
 |      Returns the bounding box, in local space including bounds extension(s), of the StaticMesh asset
 |
 |      Returns:
 |          Box:
 |
 |  get_bounds(...)
 |      x.get_bounds() -> BoxSphereBounds
 |      Returns the number of bounds of the mesh.
 |
 |      Returns:
 |          BoxSphereBounds: The bounding box represented as box origin with extents and also a sphere that encapsulates that box
 |
 |  get_material(...)
 |      x.get_material(material_index) -> MaterialInterface
 |      Gets a Material given a Material Index and an LOD number
 |
 |      Args:
 |          material_index (int32):
 |
 |      Returns:
 |          MaterialInterface: Requested material
 |
 |  get_material_index(...)
 |      x.get_material_index(material_slot_name) -> int32
 |      Gets a Material index given a slot name
 |
 |      Args:
 |          material_slot_name (Name):
 |
 |      Returns:
 |          int32: Requested material
 |
 |  get_num_lods(...)
 |      x.get_num_lods() -> int32
 |      Returns the number of LODs used by the mesh.
 |
 |      Returns:
 |          int32:
 |
 |  get_num_sections(...)
 |      x.get_num_sections(lod) -> int32
 |      Returns number of Sections that this StaticMesh has, in the supplied LOD (LOD 0 is the highest)
 |
 |      Args:
 |          lod (int32):
 |
 |      Returns:
 |          int32:
 |
 |  remove_socket(...)
 |      x.remove_socket(socket) -> None
 |      Remove a socket object in this StaticMesh by providing it's pointer. Use FindSocket() if needed.
 |
 |      Args:
 |          socket (StaticMeshSocket):
 |
 |  set_material(...)
 |      x.set_material(material_index, new_material) -> None
 |      Sets a Material given a Material Index
 |
 |      Args:
 |          material_index (int32):
 |          new_material (MaterialInterface):
 |
 |  ----------------------------------------------------------------------
 |  Data descriptors defined here:
 |
 |  lod_for_collision
 |      (int32): [Read-Write] Specifies which mesh LOD to use for complex (per-poly) collision.
 |      Sometimes it can be desirable to use a lower poly representation for collision to reduce memory usage, improve performance and behaviour.
 |      Collision representation does not change based on distance to camera.
 |
 |  lpv_bias_multiplier
 |      (float): [Read-Only] Bias multiplier for Light Propagation Volume lighting
 |
 |  ----------------------------------------------------------------------
 |  Data descriptors inherited from StreamableRenderAsset:
 |
 |  global_force_mip_levels_to_be_resident
 |      (bool): [Read-Only] Global and serialized version of ForceMiplevelsToBeResident.
 |
 |  never_stream
 |      (bool): [Read-Write] Never Stream
 |
 |  num_cinematic_mip_levels
 |      (int32): [Read-Write] Number of mip-levels to use for cinematic quality.
 |
 |  ----------------------------------------------------------------------
 |  Methods inherited from _ObjectBase:
 |
 |  __hash__(...)
 |      x.__hash__() <==> hash(x)
 |
 |  __init__(...)
 |      x.__init__(...) initializes x; see help(type(x)) for signature
 |
 |  __str__(...)
 |      x.__str__() <==> str(x)
 |
 |  cast(...)
 |      X.cast(object) -> Object -- cast the given object to this Unreal object type
 |
 |  get_class(...)
 |      x.get_class() -> Class -- get the Unreal class of this instance
 |
 |  get_default_object(...)
 |      X.get_default_object() -> Object -- get the Unreal class default object (CDO) of this type
 |
 |  get_editor_property(...)
 |      x.get_editor_property(name) -> object -- get the value of any property visible to the editor
 |
 |  get_fname(...)
 |      x.get_fname() -> FName -- get the name of this instance
 |
 |  get_full_name(...)
 |      x.get_full_name() -> str -- get the full name (class name + full path) of this instance
 |
 |  get_name(...)
 |      x.get_name() -> str -- get the name of this instance
 |
 |  get_outer(...)
 |      x.get_outer() -> Object -- get the outer object from this instance (if any)
 |
 |  get_outermost(...)
 |      x.get_outermost() -> Package -- get the outermost object (the package) from this instance
 |
 |  get_path_name(...)
 |      x.get_path_name() -> str -- get the path name of this instance
 |
 |  get_typed_outer(...)
 |      x.get_typed_outer(type) -> type() -- get the first outer object of the given type from this instance (if any)
 |
 |  get_world(...)
 |      x.get_world() -> World -- get the world associated with this instance (if any)
 |
 |  modify(...)
 |      x.modify(bool) -> bool -- inform that this instance is about to be modified (tracks changes for undo/redo if transactional)
 |
 |  rename(...)
 |      x.rename(name=None, outer=None) -> bool -- rename this instance
 |
 |  set_editor_property(...)
 |      x.set_editor_property(name, value) -> None -- set the value of any property visible to the editor, ensuring that the pre/post change notifications are called
 |
 |  static_class(...)
 |      X.static_class() -> Class -- get the Unreal class of this type
 |
 |  ----------------------------------------------------------------------
 |  Data and other attributes inherited from _ObjectBase:
 |
 |  __new__ = <built-in method __new__ of type object>
 |      T.__new__(S, ...) -> a new object with type S, a subtype of T
LogPython: None



LogPython: import sys
LogPython: for path in sys.path:
    print path
LogPython: D:\Github\UnrealEngine\Engine\Binaries\ThirdParty\Python\Win64\python27.zip
LogPython: D:\Github\UnrealEngine\Engine\Binaries\ThirdParty\Python\Win64\DLLs
LogPython: D:\Github\UnrealEngine\Engine\Binaries\ThirdParty\Python\Win64\lib
LogPython: D:\Github\UnrealEngine\Engine\Binaries\ThirdParty\Python\Win64\lib\plat-win
LogPython: D:\Github\UnrealEngine\Engine\Binaries\ThirdParty\Python\Win64\lib\lib-tk
LogPython: D:\Github\UnrealEngine\Engine\Binaries\Win64
LogPython: D:\Github\UnrealEngine\Engine\Binaries\ThirdParty\Python\Win64
LogPython: D:\Github\UnrealEngine\Engine\Binaries\ThirdParty\Python\Win64\lib\site-packages
LogPython: C:/Users/victor.l/Documents/UnrealEngine/Python
LogPython: D:/Github/UnrealEngine/Engine/Content/Python
LogPython: D:/Unreal Projects/IGGTestProject/Content/Python
LogPython: D:/Github/UnrealEngine/Engine/Plugins/2D/Paper2D/Content/Python
LogPython: D:/Github/UnrealEngine/Engine/Plugins/Developer/AnimationSharing/Content/Python
LogPython: D:/Github/UnrealEngine/Engine/Plugins/Editor/CryptoKeys/Content/Python
LogPython: D:/Github/UnrealEngine/Engine/Plugins/Editor/CurveEditorTools/Content/Python
LogPython: D:/Github/UnrealEngine/Engine/Plugins/Enterprise/DatasmithContent/Content/Python
LogPython: D:/Github/UnrealEngine/Engine/Plugins/Experimental/AutomationUtils/Content/Python
LogPython: D:/Github/UnrealEngine/Engine/Plugins/Experimental/PythonScriptPlugin/Content/Python
LogPython: D:/Github/UnrealEngine/Engine/Plugins/Lumin/MagicLeap/Content/Python
LogPython: D:/Github/UnrealEngine/Engine/Plugins/Media/MediaCompositing/Content/Python
LogPython: D:/Github/UnrealEngine/Engine/Plugins/Runtime/Oculus/OculusVR/Content/Python
LogPython: D:/Github/UnrealEngine/Engine/Plugins/Runtime/Steam/SteamVR/Content/Python
