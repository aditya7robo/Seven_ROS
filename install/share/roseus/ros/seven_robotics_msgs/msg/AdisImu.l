;; Auto-generated. Do not edit!


(when (boundp 'seven_robotics_msgs::AdisImu)
  (if (not (find-package "SEVEN_ROBOTICS_MSGS"))
    (make-package "SEVEN_ROBOTICS_MSGS"))
  (shadow 'AdisImu (find-package "SEVEN_ROBOTICS_MSGS")))
(unless (find-package "SEVEN_ROBOTICS_MSGS::ADISIMU")
  (make-package "SEVEN_ROBOTICS_MSGS::ADISIMU"))

(in-package "ROS")
;;//! \htmlinclude AdisImu.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass seven_robotics_msgs::AdisImu
  :super ros::object
  :slots (_header _gyro_latest _accel_latest ))

(defmethod seven_robotics_msgs::AdisImu
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:gyro_latest __gyro_latest) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:accel_latest __accel_latest) (make-array 3 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _gyro_latest __gyro_latest)
   (setq _accel_latest __accel_latest)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:gyro_latest
   (&optional __gyro_latest)
   (if __gyro_latest (setq _gyro_latest __gyro_latest)) _gyro_latest)
  (:accel_latest
   (&optional __accel_latest)
   (if __accel_latest (setq _accel_latest __accel_latest)) _accel_latest)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float32[3] _gyro_latest
    (* 4    3)
    ;; float32[3] _accel_latest
    (* 4    3)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float32[3] _gyro_latest
     (dotimes (i 3)
       (sys::poke (elt _gyro_latest i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _accel_latest
     (dotimes (i 3)
       (sys::poke (elt _accel_latest i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float32[3] _gyro_latest
   (dotimes (i (length _gyro_latest))
     (setf (elt _gyro_latest i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _accel_latest
   (dotimes (i (length _accel_latest))
     (setf (elt _accel_latest i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;;
   self)
  )

(setf (get seven_robotics_msgs::AdisImu :md5sum-) "8efc0599b85bed911286b8a088cbacc9")
(setf (get seven_robotics_msgs::AdisImu :datatype-) "seven_robotics_msgs/AdisImu")
(setf (get seven_robotics_msgs::AdisImu :definition-)
      "Header header

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

")



(provide :seven_robotics_msgs/AdisImu "8efc0599b85bed911286b8a088cbacc9")


