// Auto-generated. Do not edit!

// (in-package seven_robotics_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class AdisImu {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.gyro_latest = null;
      this.accel_latest = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('gyro_latest')) {
        this.gyro_latest = initObj.gyro_latest
      }
      else {
        this.gyro_latest = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('accel_latest')) {
        this.accel_latest = initObj.accel_latest
      }
      else {
        this.accel_latest = new Array(3).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type AdisImu
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Check that the constant length array field [gyro_latest] has the right length
    if (obj.gyro_latest.length !== 3) {
      throw new Error('Unable to serialize array field gyro_latest - length must be 3')
    }
    // Serialize message field [gyro_latest]
    bufferOffset = _arraySerializer.float32(obj.gyro_latest, buffer, bufferOffset, 3);
    // Check that the constant length array field [accel_latest] has the right length
    if (obj.accel_latest.length !== 3) {
      throw new Error('Unable to serialize array field accel_latest - length must be 3')
    }
    // Serialize message field [accel_latest]
    bufferOffset = _arraySerializer.float32(obj.accel_latest, buffer, bufferOffset, 3);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type AdisImu
    let len;
    let data = new AdisImu(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [gyro_latest]
    data.gyro_latest = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [accel_latest]
    data.accel_latest = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'seven_robotics_msgs/AdisImu';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8efc0599b85bed911286b8a088cbacc9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    float32[3] gyro_latest	#gyro latest measurements [rad/s]
    float32[3] accel_latest #accel latest measurements [m/s^2]
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    # 0: no frame
    # 1: global frame
    string frame_id
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new AdisImu(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.gyro_latest !== undefined) {
      resolved.gyro_latest = msg.gyro_latest;
    }
    else {
      resolved.gyro_latest = new Array(3).fill(0)
    }

    if (msg.accel_latest !== undefined) {
      resolved.accel_latest = msg.accel_latest;
    }
    else {
      resolved.accel_latest = new Array(3).fill(0)
    }

    return resolved;
    }
};

module.exports = AdisImu;
