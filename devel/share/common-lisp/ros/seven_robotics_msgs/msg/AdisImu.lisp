; Auto-generated. Do not edit!


(cl:in-package seven_robotics_msgs-msg)


;//! \htmlinclude AdisImu.msg.html

(cl:defclass <AdisImu> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (gyro_latest
    :reader gyro_latest
    :initarg :gyro_latest
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (accel_latest
    :reader accel_latest
    :initarg :accel_latest
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass AdisImu (<AdisImu>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AdisImu>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AdisImu)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name seven_robotics_msgs-msg:<AdisImu> is deprecated: use seven_robotics_msgs-msg:AdisImu instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <AdisImu>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader seven_robotics_msgs-msg:header-val is deprecated.  Use seven_robotics_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'gyro_latest-val :lambda-list '(m))
(cl:defmethod gyro_latest-val ((m <AdisImu>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader seven_robotics_msgs-msg:gyro_latest-val is deprecated.  Use seven_robotics_msgs-msg:gyro_latest instead.")
  (gyro_latest m))

(cl:ensure-generic-function 'accel_latest-val :lambda-list '(m))
(cl:defmethod accel_latest-val ((m <AdisImu>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader seven_robotics_msgs-msg:accel_latest-val is deprecated.  Use seven_robotics_msgs-msg:accel_latest instead.")
  (accel_latest m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AdisImu>) ostream)
  "Serializes a message object of type '<AdisImu>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'gyro_latest))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'accel_latest))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AdisImu>) istream)
  "Deserializes a message object of type '<AdisImu>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'gyro_latest) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'gyro_latest)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'accel_latest) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'accel_latest)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AdisImu>)))
  "Returns string type for a message object of type '<AdisImu>"
  "seven_robotics_msgs/AdisImu")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AdisImu)))
  "Returns string type for a message object of type 'AdisImu"
  "seven_robotics_msgs/AdisImu")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AdisImu>)))
  "Returns md5sum for a message object of type '<AdisImu>"
  "8efc0599b85bed911286b8a088cbacc9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AdisImu)))
  "Returns md5sum for a message object of type 'AdisImu"
  "8efc0599b85bed911286b8a088cbacc9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AdisImu>)))
  "Returns full string definition for message of type '<AdisImu>"
  (cl:format cl:nil "Header header~%~%float32[3] gyro_latest	#gyro latest measurements [rad/s]~%float32[3] accel_latest #accel latest measurements [m/s^2]~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AdisImu)))
  "Returns full string definition for message of type 'AdisImu"
  (cl:format cl:nil "Header header~%~%float32[3] gyro_latest	#gyro latest measurements [rad/s]~%float32[3] accel_latest #accel latest measurements [m/s^2]~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AdisImu>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'gyro_latest) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'accel_latest) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AdisImu>))
  "Converts a ROS message object to a list"
  (cl:list 'AdisImu
    (cl:cons ':header (header msg))
    (cl:cons ':gyro_latest (gyro_latest msg))
    (cl:cons ':accel_latest (accel_latest msg))
))
