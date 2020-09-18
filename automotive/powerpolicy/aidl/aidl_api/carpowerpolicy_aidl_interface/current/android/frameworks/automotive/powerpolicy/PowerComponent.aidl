///////////////////////////////////////////////////////////////////////////////
// THIS FILE IS IMMUTABLE. DO NOT EDIT IN ANY CASE.                          //
///////////////////////////////////////////////////////////////////////////////

// This file is a snapshot of an AIDL interface (or parcelable). Do not try to
// edit this file. It looks like you are doing that because you have modified
// an AIDL interface in a backward-incompatible way, e.g., deleting a function
// from an interface or a field from a parcelable and it broke the build. That
// breakage is intended.
//
// You must not make a backward incompatible changes to the AIDL files built
// with the aidl_interface module type with versions property set. The module
// type is used to build AIDL files in a way that they can be used across
// independently updatable components of the system. If a device is shipped
// with such a backward incompatible change, it has a high risk of breaking
// later when a module using the interface is updated, e.g., Mainline modules.

package android.frameworks.automotive.powerpolicy;
@Backing(type="int") @VintfStability
enum PowerComponent {
  AUDIO = 1,
  MEDIA = 2,
  DISPLAY_MAIN = 3,
  DISPLAY_CLUSTER = 4,
  DISPLAY_FRONT_PASSENGER = 5,
  DISPLAY_REAR_PASSENGER = 6,
  BLUETOOTH = 7,
  WIFI = 8,
  CELLULAR = 9,
  ETHERNET = 10,
  PROJECTION = 11,
  NFC = 12,
  INPUT = 13,
  VOICE_INTERACTION = 14,
  VISUAL_INTERACTION = 15,
  TRUSTED_DEVICE_DETECTION = 16,
}
