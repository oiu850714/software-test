pipeline {
    agent {
        docker {
            image 'gcc'
        }
    }
    stages {
        stage('Build') {
            steps {
                sh 'git submodule update --init --recursive'
                sh 'make -C homework/HW1/triangle_problem_test'
                sh 'make -C homework/HW1/NextDate_problem_test'
                sh 'make -C homework/HW1/Commission_problem_test'
            }
        }
        stage('Test') {
            steps {
                sh 'homework/HW1/triangle_problem_test/triangle_verifier_unittest'
                sh 'homework/HW1/NextDate_problem_test/NextDate_verifier_unittest'
                sh 'homework/HW1/Commission_problem_test/Commission_verifier_unittest'
            }
        }
    }
}
