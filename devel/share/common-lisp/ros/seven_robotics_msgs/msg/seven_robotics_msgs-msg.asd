
(cl:in-package :asdf)

(defsystem "seven_robotics_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "AdisImu" :depends-on ("_package_AdisImu"))
    (:file "_package_AdisImu" :depends-on ("_package"))
  ))