pipeline {
    agent any

    environment {
        DOCKER_IMAGE = 'tank_fire'
        DOCKER_CONTAINER = 'tank_firecontainer'
        GIT_REPO = 'https://github.com/chantouRichard/Tank-fire.git'
        DOCKER_BUILDKIT = '0'  // 禁用 BuildKit
    }

    stages {
        stage('Checkout') {
            steps {
                // 拉取代码
                git branch: 'main', url: "${env.GIT_REPO}"
            }
        }

        stage('Build Docker Image') {
            steps {
                script {
                    // 构建 Docker 镜像
                    sh 'docker build -t ${DOCKER_IMAGE} .'
                }
            }
        }

        stage('Run Docker Container') {
            steps {
                script {
                    // 停止并删除旧的容器（如果存在）
                    sh 'docker stop ${DOCKER_CONTAINER} || true'
                    sh 'docker rm ${DOCKER_CONTAINER} || true'

                    // 运行新的容器
                    sh 'docker run -d --name ${DOCKER_CONTAINER} -p 80:80 ${DOCKER_IMAGE}'
                }
            }
        }
    }

    post {
        always {
            // 清理工作
            sh 'docker system prune -f'
        }
        success {
            echo 'Deployment successful!'
        }
        failure {
            echo 'Deployment failed!'
        }
    }
}
